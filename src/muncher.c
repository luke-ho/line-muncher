#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include "line_reader.h"
#include "line_buffer.h"

#define BUFFER_MAX_SIZE 4096

static char buffer[BUFFER_MAX_SIZE+1];

static LineReader lineReader;
static LineBuffer lineBuffer;

static void signal_handler(int signo) 
{
    fprintf(stderr, "Child received exit signal(%d), exiting!\n", signo);
    line_reader_list_cleanup(&lineReader.positions);
    line_buffer_list_cleanup(&lineBuffer.lines);
    exit(0);
}

static void register_signal_handlers() 
{
    if (signal(SIGUSR1,signal_handler) == SIG_ERR) {
        perror("Error while trying to create signal handler SIGUSR1\n");
        exit(1);
    }

    if (signal(SIGTERM,signal_handler) == SIG_ERR) {
        perror("Error while trying to create signal handler SIGTERM\n");
        exit(1);
    }
}

static int read_line(char * buffer, int num_bytes) 
{
    int start = 0, end = 0;
    int i;
    int line_added = 0;
    if ( !buffer ) return -1;

    for ( i = 0; i < BUFFER_MAX_SIZE && i < num_bytes ; ++i ) {
        if (buffer[i] == '\n' || buffer[i] == '\r') {
            line_added = 1;
            end = i;
            line_reader_list_add(&lineReader.positions, start, end);
            start = i+1;
        }
    }

    if ( line_added == 0 && start == 0 && i > 0 ) {
        if ( i == BUFFER_MAX_SIZE ) {
            // Encountered a really large line.  Add to the buffer and continue
            //printf("(1) Adding to buffer for: (%s)\n", &buffer[start]);
            if (start < BUFFER_MAX_SIZE) 
                line_buffer_list_add(&lineBuffer.lines, &buffer[start]);

            return 0;
        } else {
            // Encountered just a one-line file that could fit into the buffer.
            line_reader_list_add(&lineReader.positions, start, i);
            return 1;
        }
    }

    // Figure out if we need to add to buffer
    if (start >= end && i != start && start < BUFFER_MAX_SIZE) {
        //printf("(2) Adding to buffer for: (%s)\n", &buffer[start]);
        line_buffer_list_add(&lineBuffer.lines, &buffer[start]);
    } 

    if ( line_added == 1 ) 
        return 1;
    else
        return 0;
}

static void print_buffer()
{
   LineBufferListNode * current = lineBuffer.lines.head;
   LineBufferListNode * current_trailer = NULL;
   while ( current != NULL ) {
       current_trailer = current;
       printf("%s", current->val);
       current = current->next;
       free(current_trailer->val);
       free(current_trailer);
       current_trailer = NULL;
   }
   if ( current_trailer ) {
       free(current_trailer->val);
       free(current_trailer);
   }
   lineBuffer.lines.head = NULL;
}

static void print_reader()
{
   LineReaderListNode * current = lineReader.positions.head;
   LineReaderListNode * current_trailer = NULL; 
   while(current) {
       current_trailer = current;
       buffer[current->end] = '\0';
       printf("%s\n", &buffer[current->start]);

       current = current->next;
       free(current_trailer);
       current_trailer = NULL;
   }
   if (current_trailer) 
       free(current_trailer);

   lineReader.positions.head = NULL;

}

int main(int argc, char ** argv) 
{
    if ( argc != 2 ) {
        fprintf(stderr, "Usage: <filename>\n");
        exit(1);
    }
    int fd[2];
    pid_t childpid;
    pipe(fd);

    if ((childpid = fork()) == -1) {
        perror("Issue while forking, exiting!\n");
        exit(1);
    }

    if (childpid == 0) {
        // We are the child.  Close the input side of pipe
        close(fd[0]);

        register_signal_handlers();
        printf("(%d), SIGUSR1:%d\n", getpid(), SIGUSR1);
        printf("kill -%d %d\n", SIGUSR1, getpid());
        printf("filename:(%s)\n", argv[1]);
        FILE * inputFile = fopen(argv[1], "r");
        int num_bytes = 0;
        int ret;
        if ( !inputFile ) {
            fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
            exit(1);
        }
        // Init lineReader and lineBuffer
        lineReader.positions.head = NULL;
        lineBuffer.lines.head = NULL;
        // Read in from file
        while((num_bytes = fread(buffer, 1, BUFFER_MAX_SIZE, inputFile)) > 0) {
            ret = read_line(buffer, num_bytes);

            if (lineBuffer.lines.head) {
               if ( ret == 0 ) {
                   print_buffer();
               } else if ( ret == 1 ) {
                   if (lineReader.positions.head) {
                       print_reader();
                   }
                   print_buffer();
               } 
            } else if (lineReader.positions.head) {
               // We have nothing in the buffer, print every line
               print_reader();
            }
        }

        if ( lineBuffer.lines.head ) {
           print_buffer();
        }
        printf("Closing: %s\n", argv[1]);
        fclose(inputFile);
    } else {
        // We are parent process.  Close the output side of pipe
        close(fd[1]);
    }
    return 0;
}

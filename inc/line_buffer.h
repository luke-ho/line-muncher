#ifndef __LINE_BUFFER__
#define __LINE_BUFFER__

#include <string.h>

typedef struct _line_buffer_list_node {
    char * val;
    struct _line_buffer_list_node * next;
} LineBufferListNode;

typedef struct _line_buffer_list {
    struct _line_buffer_list_node * head;
} LineBufferList;

typedef struct _lineBuffer {
    LineBufferList lines;
} LineBuffer;

void line_buffer_list_add(LineBufferList * list, char * val) {
    if ( !list ) return;
    if ( list->head == NULL ) {
        list->head = (LineBufferListNode *) malloc(sizeof(LineBufferListNode));
        list->head->val = strdup(val);
        list->head->next = NULL;
    } else {
        LineBufferListNode * current = list->head;
        while ( current->next != NULL ) {
            current = current->next;
        }
        current->next = (LineBufferListNode *) malloc(sizeof(LineBufferListNode));
        current->next->val = strdup(val);
        current->next->next = NULL;
    }
}

void line_buffer_list_print(LineBufferList * list) {
    if ( !list ) return;
    LineBufferListNode * current = list->head;
    while ( current != NULL ) {
        printf("val:(%s)\n", current->val);
        current = current->next;
    }
}

void line_buffer_list_cleanup(LineBufferList * list) {
    if ( !list ) return;
    LineBufferListNode * current = list->head;
    LineBufferListNode * tmp     = list->head;

    while ( tmp != NULL ) {
        tmp = current->next;
        free(current->val);
        free(current);
        current = tmp;
    }
}


#endif

#ifndef __LINE_READER__
#define __LINE_READER__

typedef struct _lineReader_list_node {
    int start;
    int end;
    struct _lineReader_list_node * next;
} LineReaderListNode;

typedef struct _lineReader_list {
    struct _lineReader_list_node * head;
} LineReaderList;

typedef struct _lineReader {
    LineReaderList positions;
} LineReader;

void line_reader_list_add(LineReaderList * list, int start, int end) {
    if ( !list ) return;
    if ( list->head == NULL ) {
        list->head = (LineReaderListNode *) malloc(sizeof(LineReaderListNode));
        list->head->start = start;
        list->head->end = end;
        list->head->next = NULL;
    } else {
        LineReaderListNode * current = list->head;
        while ( current->next != NULL ) {
            current = current->next;
        }
        current->next = (LineReaderListNode *) malloc(sizeof(LineReaderListNode));
        current->next->start = start;
        current->next->end = end;
        current->next->next = NULL;
    }
}

void line_reader_list_print(LineReaderList * list) {
    if ( !list ) return;
    LineReaderListNode * current = list->head;
    while ( current != NULL ) {
        printf("start:(%d), end:(%d)\n", current->start, current->end);
        current = current->next;
    }
}

void line_reader_list_cleanup(LineReaderList * list) {
    if ( !list ) return;
    LineReaderListNode * current = list->head;
    LineReaderListNode * tmp     = list->head;

    while ( tmp != NULL ) {
        tmp = current->next;
        free(current);
        current = tmp;
    }
}
#endif

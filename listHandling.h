#ifndef LISTHANDL_H_
#define LISTHANDL_H_

#define MAX_HEAP_SIZE 102400000
#define PROGRAM_BREAK_ADDER 128

extern char heap[];
extern char *programBreak;

typedef struct node{
    size_t sz;
    struct node* Next;
    struct node* Pre;
}node;

extern node *head;

void printList();
void createNode(node *nodePlace, size_t nodeSize);
int deleteNode(node * nodePlace);

#endif

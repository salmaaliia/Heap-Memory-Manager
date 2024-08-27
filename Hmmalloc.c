#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "listHandling.h"
#include "Hmmsbrk.h"
#include "Hmmalloc.h"

//char *heapStart = heap;

char *heapStart;

void log_message(const char *msg) {
    int fd = open("heap_debug.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd != -1) {
        write(fd, msg, strlen(msg));
        close(fd);
    }
}

void* Hmmalloc(size_t size) {
    node *ptr = NULL;
    void *retPtr = NULL;
//        char buf[100];
//    snprintf(buf, sizeof(buf), "Hmmalloc called with size %zu\n", size);
//    log_message(buf);
//    static char *mypbk;
    if(size < 0)
            return NULL;
    size_t best = MAX_HEAP_SIZE;

    // Ensure size includes padding for alignment (if needed)
    if (size % sizeof(int) != 0) {
            size = (size + sizeof(int) - 1) & ~(sizeof(int) - 1);
    }

    // Check if the size is smaller than the node size; if it is, increment the size to prevent issues when freeing the memory.
    int totalSize = size + sizeof(size_t);
    if(totalSize < sizeof(node))
    {
            totalSize = sizeof(node);
    }
    // check if the free list is empty and add a new node by incrementing the program break and adding new node.
    if (head == NULL) {
            char *localProgramBreak = sbrk(0);
            size_t rem = totalSize % PROGRAM_BREAK_ADDER;
            size_t div = totalSize / PROGRAM_BREAK_ADDER,incPB = 0;
            incPB = (rem == 0)? div : div + 1;

            incPB *= 2;
            if(Hmmsbrk(incPB * PROGRAM_BREAK_ADDER) != (void *)-1) {
                    createNode((node *) localProgramBreak, incPB * PROGRAM_BREAK_ADDER);
            }
            else
                    return NULL;
    }


    // we use best fit to search for suitable node.
    node *temp = (node*)head;
    do {
        if (temp->sz >= totalSize) {
            if ((temp->sz) <= best) {
                ptr = temp;
                best = temp->sz;
            }
        }
        temp = temp->Next;
    } while (temp != head);


    // If no suitable nodes, increment the program break and add a new node
    node *lastNode = head->Pre;
    if (ptr == NULL) {
            size_t lastSZ = lastNode->sz;
           // char *localProgramBreak = programBreak;
            char *localProgramBreak = sbrk(0);
	    size_t incrPB = totalSize / PROGRAM_BREAK_ADDER;
	    intptr_t incr = 0;
           
	    if(totalSize < PROGRAM_BREAK_ADDER){
		    incr = 2 * PROGRAM_BREAK_ADDER;
		    Hmmsbrk(2 * PROGRAM_BREAK_ADDER);
	    }
            else{
                    if(totalSize % PROGRAM_BREAK_ADDER == 0){
			    incr = (incrPB * 2) * PROGRAM_BREAK_ADDER;
		      	    Hmmsbrk((incrPB * 2) * PROGRAM_BREAK_ADDER);
		    }
                    else{
			    incr = ((incrPB + 1) * 2) * PROGRAM_BREAK_ADDER;
                            Hmmsbrk(((incrPB + 1) * 2) * PROGRAM_BREAK_ADDER);
		    }
            }

        //Combine the new node with the last node in the list if this last node is immediately before the old program break

            if(((size_t)(localProgramBreak - (char*)lastNode)) == lastSZ)
            {
		    lastNode->sz = lastSZ + incr;
//                    deleteNode(lastNode);
//                    createNode(lastNode, lastSZ + (size_t)(programBreak - localProgramBreak));
		   
   	    }
            else
            {
		    createNode((node*)localProgramBreak, (size_t)(incr));
//                    createNode((node*)localProgramBreak, (size_t)(programBreak - localProgramBreak));
            }
            ptr = head->Pre;
    }

    // After finding a suitable node check if we can split this node(after spliting the nodes must be larger than the size of the node) 
    if (ptr != NULL){
            deleteNode(ptr);

            if((ptr->sz - totalSize) >= sizeof(node))
            {
                    node *newNode = (node*)((char*)ptr + totalSize);
                    createNode(newNode, (size_t)(ptr->sz - totalSize));
            }
            else
            {
                    totalSize = ptr->sz;
            }

            size_t *nodeSize = (size_t*)ptr;
            *nodeSize = totalSize;
            retPtr = (void*)((char*)ptr + sizeof(size_t));
    }
    return retPtr;
}


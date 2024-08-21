#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "listHandling.h"
#include "Hmmsbrk.h"
#include "Hmmfree.h"

void Hmmfree(void *ptr)
{
    if(ptr == NULL)
        return;

    // decrement the the ptr by the size of size_t to acess the whole allocated space including the size of the allocated area
    size_t *ptrStart = (size_t *)((char *)ptr - sizeof(size_t));
    size_t blockSize = *ptrStart;

    createNode((node*)ptrStart, (size_t)(blockSize));

    // Loop over the list to combine any contiguous nodes

    node *temp = head;
    do {
            while (temp->Next != head && (size_t)((char *)temp->Next - (char *)temp) == temp->sz)
            {
                    node * myNext = temp->Next;
                    temp->sz += myNext->sz;
                    temp->Next = myNext->Next;
                    deleteNode(myNext);
            }
            temp = temp->Next;
    } while (temp != head);

    if (!head || !head->Pre) {
            return;
    }

    // If there is a lot of free space in the end of the list, decrement the program break
    node *tail = head->Pre;
    size_t tailSZ = tail->sz;
    intptr_t res = tail->sz;
    size_t incrPB = tailSZ / PROGRAM_BREAK_ADDER;
    if(tailSZ > PROGRAM_BREAK_ADDER && ((size_t)(programBreak - (char *) tail) == tail->sz) ){
	    void *result = Hmmsbrk(-res);
	    if (result != (void *)-1) {
		    deleteNode(tail);
	    }
    }
        

 }


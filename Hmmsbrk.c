#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "listHandling.h"
#include "Hmmsbrk.h"


void * Hmmsbrk(intptr_t incrPB)
{
        char *oldProgramBreak = programBreak;
        char *newProgramBreak = programBreak + incrPB;
        if (newProgramBreak >= heap && newProgramBreak <= (heap + MAX_HEAP_SIZE))
        {
                programBreak = newProgramBreak;
                return oldProgramBreak;
        }
        else
        {
                return (void *)-1;
        }

}


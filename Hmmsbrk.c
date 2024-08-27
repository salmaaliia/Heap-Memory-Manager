#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "listHandling.h"
#include "Hmmsbrk.h"

#define PROGRAM 1

void * Hmmsbrk(intptr_t incrPB)
{
	char *oldProgramBreak;
        char *newProgramBreak;
	if(PROGRAM)
	{
	//	oldProgramBreak = sbrk(incrPB);
	//	programBreak = sbrk(0);
		return sbrk(incrPB);

	}
	else
	{
        oldProgramBreak = programBreak;
        newProgramBreak = programBreak + incrPB;
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
}


#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "listHandling.h"
#include "Hmmsbrk.h"
#include "Hmmalloc.h"
#include "Hmmfree.h"
#include "Hmmrealloc.h"

void *Hmmrealloc(void *ptr, size_t size){
	if(ptr == NULL)
	{
		return Hmmalloc(size);
	}

	if(size == 0)
	{
		Hmmfree(ptr);
		return NULL;
	}

	void* newPtr = Hmmalloc(size);
    
	if (newPtr == NULL) {
		return NULL;
    	}

	size_t *ptrStart = (size_t *)((char *)ptr - sizeof(size_t));

	size_t oldSize = *ptrStart;
    
	size_t copySize = oldSize < size ? oldSize : size;
    
	memcpy(newPtr, ptr, copySize);
    
	Hmmfree(ptr);
    
	return newPtr;

}


#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "listHandling.h"
#include "Hmmsbrk.h"
#include "Hmmalloc.h"
#include "Hmmfree.h"
#include "Hmmcalloc.h"


void *Hmmcalloc(size_t nmemb, size_t size)
{
	size_t totalSize = nmemb * size;

	void *ptr = Hmmalloc(totalSize);

	if(ptr == NULL)
	{
		return NULL;
	}

	memset(ptr, 0, totalSize);

	return ptr;

}

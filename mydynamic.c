#include <stddef.h>
#include <stdio.h>
#include <unistd.h> 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "listHandling.h"
#include "Hmmalloc.h"
#include "Hmmfree.h"
#include "Hmmcalloc.h"
#include "Hmmrealloc.h"
#include "mydynamic.h"


void * malloc(size_t size)
{
    return Hmmalloc(size);
}

void free(void *ptr)
{
    Hmmfree(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
        return Hmmcalloc(nmemb, size);
}

void *realloc(void *ptr, size_t size)
{
        return Hmmrealloc(ptr, size);
}


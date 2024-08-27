#ifndef MYDYNAMIC_H
#define MYDYNAMIC_H

void *Hmmalloc(size_t size);
void Hmmfree(void *ptr);
void *Hmmcaloc(size_t nmemb, size_t size);
void *Hmmrealloc(void *ptr, size_t size);

#endif 


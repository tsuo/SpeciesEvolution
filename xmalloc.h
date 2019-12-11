#ifndef H_XMA_H
#define H_XMA_H

void* malloc_or_exit(size_t nbytes, const char *file, int line);

#define xmalloc(nbytes) malloc_or_exit((nbytes), __FILE__, __LINE__)

#endif

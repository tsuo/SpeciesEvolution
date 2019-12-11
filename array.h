#ifndef H_ARR_H
#define H_ARR_H

#include <stdlib.h>
#include <stdio.h>
#include "xmalloc.h"

#define make_vector(v,n) ((v) = xmalloc((n) * sizeof *(v)))
#define free_vector(v) do{ free(v); v = NULL; } while(0)

#define make_matrix(a, m, n) do {				\
	size_t make_matrix_loop_counter;			\
	make_vector((a), (m) + 1);				\
	for(make_matrix_loop_counter = 0;			\
	    make_matrix_loop_counter < (m);			\
	    make_matrix_loop_counter++)				\
		make_vector((a)[make_matrix_loop_counter], n);	\
	(a)[(m)] = NULL;					\
} while (0)

#define free_matrix(a) do {						\
	if((a) != NULL)							\
	{								\
		size_t make_matrix_loop_counter;			\
		for(make_matrix_loop_counter = 0;			\
		    (a)[make_matrix_loop_counter] != NULL;		\
		    make_matrix_loop_counter++)				\
			free_vector((a)[make_matrix_loop_counter]);	\
		free_vector((a));					\
		a = NULL;						\
	}								\
} while (0)	


#define make_3matrix(a, m, n, o) do {				\
	size_t make_3matrix_loop_counter;			\
	make_vector((a), (m)+1);				\
	for(make_3matrix_loop_counter = 0;			\
		make_3matrix_loop_counter < (m);			\
		make_3matrix_loop_counter++)			\
	make_matrix((a)[make_3matrix_loop_counter], (n), (o));	\
	(a)[(m)] = NULL;					\
} while (0)

#define free_3matrix(a) do {						\
	if((a) != NULL)							\
	{								\
		size_t make_3matrix_loop_counter;			\
		for(make_3matrix_loop_counter = 0;			\
		    (a)[make_3matrix_loop_counter] != NULL;		\
		    make_3matrix_loop_counter++)				\
			free_matrix((a)[make_3matrix_loop_counter]);	\
		free_vector((a));					\
		a = NULL;						\
	}								\
} while (0)	


#define make_4matrix(a, m, n, o, p) do {				\
	size_t make_4matrix_loop_counter;			\
	make_vector((a), (m)+1);				\
	for(make_4matrix_loop_counter = 0;			\
		make_4matrix_loop_counter < (m);		\
		make_4matrix_loop_counter++)			\
	make_3matrix((a)[make_4matrix_loop_counter], (n), (o), (p)); \
	(a)[(m)] = NULL;					\
} while (0)					

#define free_4matrix(a) do {						\
	if((a) != NULL)							\
	{								\
		size_t make_4matrix_loop_counter;			\
		for(make_4matrix_loop_counter = 0;			\
		    (a)[make_4matrix_loop_counter] != NULL;		\
		    make_4matrix_loop_counter++)				\
			free_3matrix((a)[make_4matrix_loop_counter]);	\
		free_vector((a));					\
		a = NULL;						\
	}								\
} while (0)


#define print_vector(fmt, v, n) do {			\
	size_t print_vector_loop_counter;		\
	for(print_vector_loop_counter = 0;		\
		print_vector_loop_counter < (n);	\
		print_vector_loop_counter++)		\
	printf((fmt), (v)[print_vector_loop_counter]);	\
	putchar('\n');					\
} while (0)


///fmt is the format string, a is the double pointer array, n is the width of matrix
#define print_matrix(fmt, a, n) do {							\
	if((a) != NULL)									\
	{										\
		size_t print_matrix_loop_counter;					\
		for(print_matrix_loop_counter = 0;					\
			(a)[print_matrix_loop_counter] != NULL;				\
			print_matrix_loop_counter++)					\
		print_vector((fmt), (a)[print_matrix_loop_counter], n);			\
	}										\
} while (0)


#endif /*H_ARR_H*/



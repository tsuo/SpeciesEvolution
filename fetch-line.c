#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "fetch-line.h"
static char *trim_line(char *s)
{
	char comment = '#';
	char *t; //pointer for after leading whitespaces
	
	/// skip leading whitespaces
	while(isspace(*s))
		s++;

	/// t points to start of new s
	t = s;
	/// increment pointer until \0 or comment character is found
	while(*t != '\0' && *t != comment)	
		t++;
	
	/// if comment, set it to \0
	if(*t == comment)
		*t = '\0';

	/// if t isnt s, then iterate back and set all spaces
	/// to \0
	if(s != t)
	{
		t--;
		while(isspace(*t))
		{
			*t = '\0';
			t--;
		}
	}

	return s;
}

/// line number will represent the line read
char *fetch_line(char *buf, int buflen, FILE *stream, int *lineno)
{
	char *s;
	if (fgets(buf, buflen, stream) == NULL)
		return NULL;
	++*lineno;
	if (buf[strlen(buf) - 1] != '\n') {
		fprintf(stderr, "*** reading error: input line %d too "
		"long for %s’s buf[%d]\n",
		*lineno, __func__, buflen);
		exit(EXIT_FAILURE);
	}
	s = trim_line(buf);
	if (*s != '\0')
		return s;
	else
		return fetch_line(buf, buflen, stream, lineno); // recurse
}


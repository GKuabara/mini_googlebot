#ifndef _UTILITIES_H
#define _UTILITIES_H

#include "site.h"

#define boolean int
#define TRUE 1
#define FALSE 0

char *readLine(FILE *stream);
char* strPart(char* str, const void* init, const void* end);
char* strAppend(char* str, char* add);
void heap_sort(SITE **array, int n);
int count_char (char *string, char searched);
void bubble_sort(SITE **array, int len);
int char_to_int(char c);

#endif
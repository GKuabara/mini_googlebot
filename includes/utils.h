#ifndef _UTILITIES_H
#define _UTILITIES_H

char *readLine(FILE *stream);
char* strPart(char* str, const void* init, const void* end);
char* strAppend(char* str, char* add);
void quick_sort(SITE **array, int start, int end);
int count_char (char *string, char searched);
SITE* create_site_from_googlebot(FILE* fp);

#endif
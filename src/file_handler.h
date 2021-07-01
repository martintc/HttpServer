#ifndef FILE_HANDLER
#define FILE_HANDLER

#include <stdio.h>

// create full path from directory path and file
char* make_full_path(char *path, char *file);

// check is file exists
int check_existence(char *path);

FILE* get_file(char* path);

// returns the size of the file
long get_file_size(FILE *f);

// return the contents of a text file
char* get_file_contents(FILE* f, long int l);

#endif

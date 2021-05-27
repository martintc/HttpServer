#ifndef FILE_HANDLER
#define FILE_HANDLER

#include <stdio.h>

// create full path from directory path and file
char* make_full_path(char *path, char *file);

// check is file exists
int check_existence(char *path);

// return file contens
//FILE* file_contents(char *path);

FILE* get_file(char* path);

#endif

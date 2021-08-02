#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <string.h>

FILE* open_log(char* path);

void write_to_log(FILE* f, char* line);

void close_file(FILE* f);

#endif

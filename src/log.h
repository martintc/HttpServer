#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <string.h>
#include <time.h>

// Open log for writing
FILE* open_log(char* path);

// Open log file for appending to log
FILE* open_append_log(char* path);

// write a line to the log file
void write_to_log(FILE* f, char* line);

// closes the log file
void close_file(FILE* f);

#endif

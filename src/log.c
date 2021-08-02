#include "log.h"

FILE* open_log(char* path) {
  FILE* f = fopen(path, "rw");
  if (f == NULL) {
    println("Error in opening log file\n");
    return NULL;
  }
  return f;
}

void write_to_log(FILE* f, char* line) {
  if(fprintf(f, "%s\n", line) < 0) {
    printf("Error writing to log\n");
  }
}

void close_file(FILE* f) {
  fclose(f);
  f = NULL;
}

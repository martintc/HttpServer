#include "log.h"

FILE* open_log(char* path) {
  FILE* f = fopen(path, "w");
  if (f == NULL) {
    printf("Error in opening log file\n");
    return NULL;
  }
  return f;
}

FILE* open_append_log(char* path) {
  FILE* f = fopen(path, "a");
  if (f == NULL) {
    printf("Error is apending log file\n");
    return NULL;
  }
  return f;
}

void write_to_log(FILE* f, char* line) {

  time_t curtime;
  time(&curtime);

  if(fprintf(f, "%s %s %s\n",ctime(&curtime), "-", line) < 0) {
    printf("Error writing to log\n");
  }
}

void close_file(FILE* f) {
  fclose(f);
  f = NULL;
}

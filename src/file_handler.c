#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "file_handler.h"

char* make_full_path(char *path, char *file) {
  char *full_path = malloc(sizeof(path) + sizeof(file) + 1);
  strcat(full_path, path);
  strcat(full_path, file);
  return full_path;
}

int check_existence(char *path) {
  return access(path, R_OK);
}

FILE* get_file(char* path) {
  return  fopen(path, "r");
}

long int get_file_size(FILE* f) {
  long int length;
  fseek(f, 0L, SEEK_END);
  length = ftell(f);
  rewind(f);
  return length;
}
char* get_file_contents(FILE* f, long int l) {
  char* contents = malloc(sizeof(char)*l);
  for (long i = 0; i < l; i++) {
    contents[i] = fgetc(f);
  }
  return contents;
}

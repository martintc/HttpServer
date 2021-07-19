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
  /* if (()) */
  char* file_ext = get_file_extension(path);
  char type[11];
  strcpy(type, get_content_type(file_ext));
  char delim[] = "/";
  char* token = strtok(type, delim);
  if ((strcmp(token, "image")) == 0) {
    free(file_ext);
    return fopen(path, "rb");
  }
  free(file_ext);
  return  fopen(path, "r");
}

long int get_file_size(FILE* f) {
  long int length;
  fseek(f, 0L, SEEK_END);
  length = ftell(f);
  rewind(f);
  return length;
}
unsigned char* get_file_contents(FILE* f, long int l) {
  /* char* contents = malloc(sizeof(char)*l); */
  /* for (long i = 0; i < l; i++) { */
  /*   contents[i] = fgetc(f); */
  /* } */
  /* return contents; */

  unsigned char* contents = malloc(sizeof(unsigned char)*l);
  fread(contents, sizeof(unsigned char), l, f);
  return contents;

}

void get_contents(FILE* f, long int length, void* buf) {
	buf = malloc(sizeof(char)*length);
	memcpy(f, buf, length);
}

char* get_file_extension(char* path) {
  char* token = strpbrk(path, ".");
  ++token;
  return token;
}

char* get_content_type(char* extension) {
  if ((strcmp(extension, "html")) == 0) {
    return "text/html";
  } else if ((strcmp(extension, "css")) == 0) {
    return "text/css";
  } else if ((strcmp(extension, "jpeg")) == 0) {
    return "image/jpeg";
  } else if ((strcmp(extension, "png")) == 0) {
    return "image/png";
  } else if ((strcmp(extension, "gif")) == 0) {
    return "image/gif";
  } else {
    return "";
  }
}



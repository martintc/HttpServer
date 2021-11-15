#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "file_handler.h"

// TODO: Improve this function not to rely on heap allocations
void make_full_path(char *dest, char *path, char *file) {
  strcpy(dest, path);
  strcat(dest, file);
}

int check_existence(char *path) {
  return access(path, R_OK); 
}

FILE* get_file(char* path) {
  char* file_ext = get_file_extension(path);
  char type[11];
  strcat(type, get_content_type(file_ext));
  char delim[] = "/";
  char* token = strtok(type, delim);
  if (strcmp(token, "image") == 0) {
    return fopen(path, "rb");
  }
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
  static char value[15];
  if (strcmp(extension, "html") == 0) {
    strcpy(value, "text/html");
  } else if (strcmp(extension, "css") == 0) {
    strcpy(value, "text/css");
  } else if (strcmp(extension, "jpeg") == 0) {
    strcpy(value, "image/jpeg");
  } else if (strcmp(extension, "png") == 0) {
    strcpy(value, "image/png");
  } else if (strcmp(extension, "gif") == 0) {
    strcpy(value, "image/gif");
  } else {
    // do nothing
  }
  return value;
}



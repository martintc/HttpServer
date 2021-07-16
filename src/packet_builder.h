#ifndef PACKET_BUILDER
#define PACKET_BUILDER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handler.h"

struct http_header {
  char* response_code;
  char* server_name;
  char* content_length; // length of body
  char* content_type;
  char* connection_status;
};

struct http_packet {
  struct http_header* header;
  void* message_body;
};

// creates a total HTTP packet
struct http_packet* make_http_packet(char* file_path);

// make a generic 404 header
struct http_header* make_404_error();

// makes a 200 ok status header
struct http_header* make_200_ok(long int length, char* content_type);

// turns the struct representation into a sendable representation
char* get_packet_string(struct http_packet* packet);

// destroys the http_packet struct by freeing up the memory
void destroy_http_packet(struct http_packet* h);

#endif

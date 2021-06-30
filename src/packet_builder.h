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
  char* message_body;
};

struct http_packet* make_http_packet(char* file_path);

struct http_header* make_404_error();

struct http_header* make_200_ok(long int length);

char* get_packet_string(struct http_packet* packet);

#endif

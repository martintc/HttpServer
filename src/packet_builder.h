#ifndef PACKET_BUILDER
#define PACKET_BUILDER

#include <stdio.h>
#include <stdlib.h>
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

struct http_header* make_normal_response(char *file_path);

#endif

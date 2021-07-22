#ifndef PACKET_PARSER
#define PACKET_PARSER

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct packet_request {
  char request_method[8];
  char request_resource[256];
  char host[32];
};

// parses a packet
struct packet_request* parse_request(char* message);

// frees the memory in the parsed packet
void destroy_packet(struct packet_request* packet);

#endif

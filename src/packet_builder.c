#include "packet_builder.h"

struct http_packet* make_http_packet(char* file_path) {
  struct http_packet* packet = (struct http_packet*) malloc(sizeof(struct http_packet));
  if (check_existence(file_path) < 0) {
    packet->header = make_404_error();
    packet->message_body = "";
    return packet;
  }

  return NULL; // temporary for WIP
}

struct http_header* make_404_error() {
  struct http_header* header = (struct http_header*) malloc(sizeof(struct http_header));
  header->response_code = "404 NOT FOUND";
  header->server_name = "SERVER: Todd's HTTP";
  header->content_length = "CONTENT-LENGTH: 0";
  header->content_type = "CONTENT-TYPE: text html";
  header->connection_status = "CONECTION: CLOSE";
  return header;


}

struct http_header* make_normal_response(char *file_path) {
  return NULL; // temp for WIP
}

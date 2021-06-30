#include "packet_builder.h"

char* get_packet_string(struct http_packet* packet) {
  char* message = (char*) malloc(sizeof(char) * 30000);
  strcat(message, packet->header->response_code);
  strcat(message, "\r\n");
  strcat(message, "SERVER: ");
  strcat(message, packet->header->server_name);
  strcat(message, "\r\n");
  strcat(message, "CONTENT-LENGTH: ");
  strcat(message, packet->header->content_length);
  strcat(message, "\r\n");
  strcat(message, "CONTENT-TYPE: ");
  strcat(message, packet->header->content_type);
  strcat(message, "\r\n");
  strcat(message, "CONNECTION: ");
  strcat(message, packet->header->connection_status);
  strcat(message, "\r\n\r\n");
  strcat(message, packet->message_body);
  return message;

}

struct http_packet* make_http_packet(char* file_path) {
  struct http_packet* packet = (struct http_packet*) malloc(sizeof(struct http_packet));
  if (check_existence(file_path) < 0) {
    packet->header = make_404_error();
    packet->message_body = "<html>Resource not found!</html>";
    return packet;
  } else {
    FILE* f = get_file(file_path);
    long int length = get_file_size(f);
    packet->header = make_200_ok(length);
    packet->message_body = get_file_contents(f, length);
    return packet;
  }
  return NULL; // temporary for WIP
}

struct http_header* make_404_error() {
  struct http_header* header = (struct http_header*) malloc(sizeof(struct http_header));
  header->response_code = "HTTP/1.1 404 NOT FOUND";
  header->server_name = "Todd's HTTP";
  header->content_length = "32";
  header->content_type = "text html";
  header->connection_status = "CLOSE";
  return header;
}

struct http_header* make_200_ok (long int length) {
  char length_string[10];
  sprintf(length_string, "%li", length);
  struct http_header* header = malloc(sizeof(struct http_header));
  header->response_code = "HTTP/1.1 200 OK";
  header->server_name = "Todd's HTTP";
  header->content_type = "text html";
  header->content_length = malloc(sizeof(char)*strlen(length_string));
  strcpy(header->content_length, length_string);
  header->connection_status = "CLOSE";
  return header;
}

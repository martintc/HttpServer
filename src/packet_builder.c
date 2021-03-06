#include "packet_builder.h"
#include "file_handler.h"

char* get_packet_string(struct http_packet* packet) {
  char* message = malloc(sizeof(char) * 8192);
  message[0] = '\0';
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
  /* strcat(message, (char*) packet->message_body); */
  return message;

}

struct http_packet* make_http_packet(char* file_path) {
  struct http_packet* packet = malloc(sizeof(struct http_packet));
  if (check_existence(file_path) < 0) {
    packet->header = make_404_error();
    packet->message_body = malloc(sizeof(char)*64);
    strcpy(packet->message_body, "<html>Resource not found!</html>");
    return packet;
  } else {
    FILE* f = get_file(file_path);
    long int length = get_file_size(f);
    char* content_type = get_content_type(get_file_extension(file_path));
    packet->header = make_200_ok(length, content_type);
    //packet->message_body = get_file_contents(f, length);
    packet->message_body = get_file_contents(f, length);
    fclose(f);
    return packet;
  }
  return NULL; // temporary for WIP
}

struct http_header* make_404_error() {
  struct http_header* header = (struct http_header*) malloc(sizeof(struct http_header));
  strcpy(header->response_code, "HTTP/1.1 404 NOT FOUND");
  strcpy(header->server_name, "Todd's HTTP");
  strcpy(header->content_length, "32");
  strcpy(header->content_type, "text/html");
  strcpy(header->connection_status, "CLOSE");
  return header;
}

struct http_header* make_200_ok (long int length, char* content_type) {
  struct http_header* header = malloc(sizeof(struct http_header));
  char length_string[10];
  sprintf(length_string, "%li", length);
  /* struct http_header* header = malloc(sizeof(struct http_header)); */
  strcpy(header->response_code, "HTTP/1.1 200 OK");
  strcpy(header->server_name, "Todd's HTTP");
  /* header->content_type = "text html"; */
  strcpy(header->content_type, content_type);
  strcpy(header->content_length, length_string);
  strcpy(header->connection_status, "CLOSE");
  return header;
}

void destroy_http_packet(struct http_packet* h) {
  free(h->header);
  free(h->message_body);
  free(h);
}


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include "file_handler.h"
#include "packet_builder.h"
#include "packet_parser.h"
#include "log.h"

#define BUFFER_SIZE 8192

#define TRUE 1
#define FALSE 0

void handler(int s) {
  // do nothing
}

int get_socket () {
  #if __NetBSD__
  return socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  #elif __linux__
  return socket(AF_INET, SOCK_STREAM, 6);
  #else
  return -1;
  #endif
}

void close_socket (int* sock) {
  #if __linux__
  close(*sock);
  /* pclose((FILE *) sock); */
  #elif __NetBSD__
  pclose((FILE *) sock);
  #endif
}

void make_server (struct sockaddr_in *server, int port) {
  server->sin_family = AF_INET;
  server->sin_port = htons(port);
  server->sin_addr.s_addr = htonl(INADDR_ANY);
}

void handle_client (int *client, char *root_folder, FILE* log) {
  char request[BUFFER_SIZE];
  ssize_t recv_message = recv(*client, request, BUFFER_SIZE, 0);
  if (recv_message == -1) {
    return;
  }
  struct packet_request* r = parse_request(request);

  if ((strcmp(r->request_resource, "/")) == 0) {
    strcpy(r->request_resource, "/index.html");
  }
  write_to_log(log, r->request_resource);
  char* requested_path = make_full_path(root_folder, r->request_resource);
  //printf("1\n");

  struct http_packet* packet = make_http_packet(requested_path);
  char* message = get_packet_string(packet);
  send(*client, message, strlen(message), 0);
  send(*client, packet->message_body, atol(packet->header->content_length), 0);
  memset(request, 0 , BUFFER_SIZE);
  memset(message, 0, strlen(message));
  memset(packet->message_body, 0, atol(packet->header->content_length));
  free(message);
  message = NULL;
  destroy_http_packet(packet);
  destroy_packet(r);
  free(requested_path);
  return;
}

int main (int argc, char *argv[]) {

  // log file path on server
  char* path = "log.txt";

  /* First argument is port, second argument is file root for server  */
  int port;
  // int status; not currently in use
  int sock;
  char *root_folder;
  struct sockaddr_in server_address;

  if (argc < 3) {
    perror("Not enough options, need atleast 3. port and path to root folder.");
    exit(1);
  } else if (argc > 3) {
    perror("Too many arguments, just need port and root folder for server.\n");
    exit(1);
  } else {
    port = atoi(argv[1]);
    root_folder = argv[2];
  }


  if((sock = get_socket()) < 0) {
    perror("Issue making socket.\n");
    exit(1);
  }

  make_server(&server_address, port);

  if ((bind(sock, (struct sockaddr *) &server_address, sizeof(struct sockaddr_in))) < 0) {
    perror("ERROR: could not bind server.\n");
    exit(1);
  }

  if ((listen(sock, 100)) < 0) {
    perror("An issue occured in listening....\n");
    exit(1);
  }

  // implement signal handler
  signal(SIGPIPE, handler);

  // open log file
  //FILE* log = open_log(path);

  while (TRUE) {
    FILE* log = open_append_log(path);
    struct sockaddr_in client_socket;
    socklen_t length = sizeof(struct sockaddr);
    int client = accept(sock, (struct sockaddr *) &client_socket, &length);
    if (client < 0) {
      write_to_log(log, "Error for client connecting");
      close(client);
      continue;
    }
    write_to_log(log, "Client connected");
    handle_client(&client, root_folder, log);
    shutdown(client, SHUT_RDWR);
    close(client);
    write_to_log(log, "Client has been handled");
    close_file(log);
  }
  close(sock);
  /* close_file(log); */

  return 0;

}

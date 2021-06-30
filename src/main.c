
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "file_handler.h"
#include "packet_builder.h"
#include "packet_parser.h"

#define BUFFER_SIZE 65536

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
  /* close((FILE *) sock); */
  pclose((FILE *) sock);
  #elif __NetBSD__
  pclose((FILE *) sock);
  #endif
}

void make_server (struct sockaddr_in *server, int port) {
  server->sin_family = AF_INET;
  server->sin_port = htons(port);
  server->sin_addr.s_addr = htonl(INADDR_ANY);
}

void handle_client (int *client, char *root_folder) {
  char request[BUFFER_SIZE];
  ssize_t recv_message = recv(*client, request, BUFFER_SIZE, 0);
  printf("Message: %s\n", request);
  if (recv_message == -1) {
    return;
  }

  struct packet_request* r = parse_request(request);
  printf("test\n");

  char* requested_path = make_full_path(root_folder, r->request_resource);
  printf("Does this resource exist: %d\n", check_existence(requested_path));

  struct http_packet* packet = make_http_packet(requested_path);
  printf("test before making packet message\n");
  char* message = get_packet_string(packet);
  printf("Packet to send: %s\n", message);
  write(*client, message, strlen(message));
  fflush(stdout);

  free(packet->header->content_length);
  free(message);
  free(packet->header);
  free(packet);
  destroy_packet(r);
  printf("end of comms\n");
}

void close_client (int *sock) {
  #if __NetBSD__
  pclose((FILE*) sock);
  #elif __linux__
  pclose((FILE*) sock);
  #endif

}

int main (int argc, char *argv[]) {
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

  if (listen(sock, 100) < 0) {
    perror("An issue occured in listening....\n");
    exit(1);
  }

  while (1) {
    struct sockaddr_in client_socket;
    socklen_t length = sizeof(struct sockaddr);
    int client = accept(sock, (struct sockaddr *) &client_socket, &length);

    if (client < 0) {
      continue;
    }

    handle_client(&client, root_folder);

    //close_client(&client);
  }

  close_socket(&sock);

  return 0;

}

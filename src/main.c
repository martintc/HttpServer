
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "file_handler.h"
#include "packet_builder.h"

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

void return_404 (int *client) {
  char *msg = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: 32\r\n\r\n<html>Resource not found!</html>";
  write(*client, msg, strlen(msg));
  fflush(stdout);
}

void handle_client (int *client, char *root_folder) {
  char request[BUFFER_SIZE];
  ssize_t recv_message = recv(*client, request, BUFFER_SIZE, 0);
  printf("Message: %s\n", request);
  if (recv_message == -1) {
    return;
  }

  char *line = strtok(request, "\n");
  char *tokens = strtok(line, " ");
  char *file_path = NULL;
  if (strcmp(tokens, "GET ")) {
    tokens = strtok(NULL, " ");
    file_path = (char*) malloc(sizeof(tokens));
    strcpy(file_path, tokens);
    printf("%s\n", file_path);
  }

  char* requested_path = make_full_path(root_folder, file_path);
  printf("Does this resource exist: %d\n", check_existence(requested_path));

  struct http_packet* packet = make_http_packet(requested_path);
  printf("test\n");
  char* message = get_packet_string(packet);
  printf("%s\n", message);
  write(*client, message, strlen(message));
  fflush(stdout);

  free(message);
  free(packet->header);
  free(packet);

  if (file_path != NULL) {
    free(file_path);
  }
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int get_socket () {

  #if __NetBSD__
  return socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  #elif __linux____
  return socket(AF_INET, SOCK_STREAM, 6);
  #else
  return -1;
  #endif
}

void make_server (struct sockaddr_in *server, int port) {
  server->sin_family = AF_INET;
  server->sin_port = htons(port);
  server->sin_addr.s_addr = htonl(INADDR_ANY);
}

int main (int argc, char *argv[]) {

  int port;
  int status;
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
  }

  return 0;

}

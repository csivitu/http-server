/*
 * This program is under GNU general public license v3
 * As a component of the HttpServer project by Josh Chatterjee as part of
 * Forkthis 2024
 */

#include "server.h"
#include "response.h"
// #include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sys/socket.h>
#include <unistd.h>

Server *MakeServer(int domain, int port, int type, int protocol, int backlog,
                   uint64_t interFace) {
  Server *srv = (Server *)malloc(sizeof(Server));

  srv->domain = domain;
  srv->type = type;
  srv->port = port;
  srv->protocol = protocol;
  srv->backlog = backlog;

  // Memory Allocation for the address, to avoid runtime error during access of srv->address
  srv->address = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
  if (srv->address == NULL) {
      perror("Failed to allocate memory for sockaddr_in");
      free(srv);
      exit(EXIT_FAILURE);
  }
  
  memset(srv->address, 0, sizeof(struct sockaddr_in));
  srv->address->sin_family = domain;
  srv->address->sin_port = htons(port);
  srv->address->sin_addr.s_addr = htonl(interFace);
  // ISSUE TEST

  srv->socket = socket(domain, type, protocol);

  printf("Domain: %d\n", srv->domain);
  printf("Type: %d\n", srv->type);
  printf("Port: %d\n", srv->port);
  printf("Protocol: %d\n", srv->protocol);
  printf("Backlog: %d\n", srv->backlog);

  if (srv->socket < 0) {
    perror("Socket Failure");
    exit(EXIT_FAILURE);
  }

  // &srv->address results in pointer to pointer. Use srv->address
  if (bind(srv->socket, (struct sockaddr *)srv->address,
           sizeof(struct sockaddr_in)) < 0) {
    perror("Bind Failure");
    exit(EXIT_FAILURE);
  }

  if (listen(srv->socket, srv->backlog) < 0) {
    perror("Listen Failure");
    exit(EXIT_FAILURE);
  }

  return srv;
}

// **Added the stop function to free the server resources**
void stop(Server *srv) {
  if (srv) {
    close(srv->socket);  // Close the server socket
    free(srv);           // Free the allocated memory for the server
    printf("Server resources freed and shutdown.\n");
  }
}

void start(Server *srv) {
  char Input_Buffer[BUFFERSIZE];
  while (1) {
    printf("Idling.....\n");
    //int addlen = sizeof(srv->address);
    socklen_t addlen = sizeof(struct sockaddr_in); 
    int newSocket =
        accept(srv->socket, (struct sockaddr *)&srv->address, &addlen);
    size_t bytes = read(newSocket, Input_Buffer, BUFFERSIZE - 1);
    if (bytes >= 0) {
      Input_Buffer[bytes] = '\0';
      puts(Input_Buffer);
    } else {
      perror("BUFFER READ ISSUE");
    }

    char *response = parseResponse(Input_Buffer, bytes);

    write(newSocket, response, strlen(response));
    close(newSocket);
  }
}
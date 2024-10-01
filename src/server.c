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
#include "logger.h"

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
      ulogger_log(LOG_ERR, "Failed to allocate memory for sockaddr_in");
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
    ulogger_log(LOG_ERR, "Socket Failure");
    perror("Socket Failure");
    exit(EXIT_FAILURE);
  }

  // &srv->address results in pointer to pointer. Use srv->address
  if (bind(srv->socket, (struct sockaddr *)srv->address,
           sizeof(struct sockaddr_in)) < 0) {
    ulogger_log(LOG_ERR, "Bind Failure");
    perror("Bind Failure");
    exit(EXIT_FAILURE);
  }

  if (listen(srv->socket, srv->backlog) < 0) {
    ulogger_log(LOG_ERR, "Listen Failure");
    perror("Listen Failure");
    exit(EXIT_FAILURE);
  }
  return srv;
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
      ulogger_log(LOG_ERR, "BUFFER READ ISSUE");
      perror("BUFFER READ ISSUE");
    }

    char *response = parseResponse(Input_Buffer, bytes);
    printf("Response: %s\n", "Working Fine");
    write(newSocket, response, strlen(response));
    close(newSocket);
  }
}

/*
 * This program is under GNU general public license v3
 * As a component of the HttpServer project by Josh Chatterjee as part of
 * Forkthis 2024
 */

#ifndef server
#define server
#include <netinet/in.h>
#include <stdint.h>

#define BUFFERSIZE 16000

typedef struct server {
  int domain;
  int type;
  int protocol;
  int port;
  int backlog;
  uint64_t interface;

  int socket;
  struct sockaddr_in *address;

} Server;

Server *MakeServer(int domain, int port, int type, int protocol, int backlog,
                   uint64_t interface);

void start(Server *srv);
#endif

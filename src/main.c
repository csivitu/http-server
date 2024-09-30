/*
 * This program is under GNU general public license v3
 * As a component of the HttpServer project by Josh Chatterjee as part of
 * Forkthis 2024
 */

#include "server.h"

#define PORT 8000
#define PROTOCOL 0
#define BACKLOG 10

int main() {
  Server *srv = (Server *)MakeServer(AF_INET, PORT, SOCK_STREAM, PROTOCOL,
                                     BACKLOG, INADDR_ANY);
  start(srv);
  return 0;
}

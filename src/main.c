/*
 * This program is under GNU general public license v3
 * As a component of the HttpServer project by Josh Chatterjee as part of
 * Forkthis 2024
 */

#include "server.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "logger.h"
#include <signal.h>

void handle_sigint(int sig) {
    ulogger_log(LOG_WARN, "Server is shutting down...");
    ulogger_close();
    exit(0);
}
int main() { 
  const char* port = getenv("PORT");
  const char* protocol = getenv("PROTOCOL");
  const char* backlog = getenv("BACKLOG");

  //signal(SIGINT, handle_sigint);
  ulogger_init("log.txt");
  ulogger_log(LOG_SUCCESS, "Server is starting on port %d...", port);
  
  
  if (port == NULL || protocol == NULL || backlog == NULL) {
    fprintf(stderr, "Environment variables PORT, PROTOCOL, and BACKLOG must be set.\n");
    return 1;
  }

  int PORT, PROTOCOL, BACKLOG;
  sscanf(port, "%d", &PORT);
  sscanf(protocol, "%d", &PROTOCOL);
  sscanf(backlog, "%d", &BACKLOG);

  Server *srv = (Server *)MakeServer(AF_INET, PORT, SOCK_STREAM, PROTOCOL,
                                     BACKLOG, INADDR_ANY);
  start(srv);

  ulogger_log(LOG_WARN, "Server has stopped.");
  ulogger_close();
  return 0;
}
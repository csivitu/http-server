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


// Signal handler for SIGINT (Ctrl+C)
void handle_sigint(int sig) {
    printf("\nCaught SIGINT (Ctrl+C), shutting down the server...\n");
    // Assuming there's a function to stop and clean up the server
    exit(0);
}

int main() {
    // Set up SIGINT handler
    signal(SIGINT, handle_sigint);

    Server *srv = (Server *)MakeServer(AF_INET, PORT, SOCK_STREAM, PROTOCOL,
                                       BACKLOG, INADDR_ANY);
    start(srv);
    return 0;
}
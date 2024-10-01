/*
 * This program is under GNU general public license v3
 * As a component of the HttpServer project by Josh Chatterjee as part of
 * Forkthis 2024
 */

#include "server.h"
#include "response.h"
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>

void sigintHandler(int sig) {
    exit(0);
}

Server *MakeServer(int domain, int port, int type, int protocol, int backlog,
                   uint64_t interface) {
    Server *srv = (Server *)malloc(sizeof(Server));

    srv->domain = domain;
    srv->type = type;
    srv->port = port;
    srv->protocol = protocol;
    srv->backlog = backlog;

    srv->address->sin_family = domain;
    srv->address->sin_port = htons(port);
    srv->address->sin_addr.s_addr = htonl(interface);

    srv->socket = socket(domain, type, protocol);
    if (srv->socket < 0) {
        perror("Socket Failure");
        exit(EXIT_FAILURE);
    }

    if (bind(srv->socket, (struct sockaddr *)&srv->address,
             sizeof(srv->address)) < 0) {
        perror("Bind Failure");
        exit(EXIT_FAILURE);
    }

    if (listen(srv->socket, srv->backlog) < 0) {
        perror("Listen Failure");
        exit(EXIT_FAILURE);
    }

    return srv;
}

void start(Server *srv) {
    char Input_Buffer[BUFFERSIZE];

    signal(SIGINT, sigintHandler);

    while (1) {
        printf("Idling.....\n");
        int addlen = sizeof(srv->address);
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

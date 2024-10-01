/*
 * This program is under GNU general public license v3
 * As a component of the HttpServer project by Josh Chatterjee as part of
 * Forkthis 2024
 */

/*
For MAC OS, Use netinet/in.h and sys/socket.h
*/
// #include <netinet/in.h>
// #include <sys/socket.h>

/*
For Windows, Use winsock2.h and ws2tcpip.h
*/
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef SOCKET sock_t;
#else
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    typedef int sock_t;
#endif

#ifndef server
#define server
#include <stdint.h>

#define BUFFERSIZE 16000

typedef struct server {
  int domain;
  int type;
  int protocol;
  int port;
  int backlog;
  /* Renamed to interFace to avoid conflict with Keyword */
  uint64_t interFace;

  int socket;
  struct sockaddr_in *address;

} Server;

Server *MakeServer(int domain, int port, int type, int protocol, int backlog,
                   uint64_t interFace);

void start(Server *srv);
#endif

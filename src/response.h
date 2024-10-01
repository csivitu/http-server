/*
 * This program is under GNU general public license v3
 * As a component of the HttpServer project by Josh Chatterjee as part of
 * Forkthis 2024
 */
#include <stdlib.h>

typedef struct {
  char *method;
  char *path;
  char *ver;
} Request;

void handleRequest(char *Input_Buffer, size_t bytes, int socket);

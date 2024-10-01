/*
 * This program is under GNU general public license v3
 * As a component of the HttpServer project by Josh Chatterjee as part of
 * Forkthis 2024
 */

#include "response.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WEBROOT "./view"

unsigned char readRequest(char *Input_Buffer, size_t bytes, Request *request) {
  char **requestItems = (char **)request;
  request->method = Input_Buffer;
  unsigned char count = 0;
  for (size_t i = 0; i < bytes; i++) {
    if (Input_Buffer[i] == ' ') {
      Input_Buffer[i] = 0;
      requestItems[++count] = Input_Buffer + i + 1;
    }
    else if (Input_Buffer[i] == '\r' || Input_Buffer[i] == '\n') {
      Input_Buffer[i] = 0;
      break;
    }
  }
  return count == 2;
}

void handleRequest(char *Input_Buffer, size_t bytes, int socket) {
  Request request;
  if (!readRequest(Input_Buffer, bytes, &request)) {
    char *response = "HTTP/1.1 400 Bad Request\r\n\r\n\r\n";
    write(socket, response, strlen(response));
    return;
  }

  if (strcmp(request.method, "GET") != 0) {
    char *response = "HTTP/1.1 405 Method Not Allowed\r\n\r\n\r\n";
    write(socket, response, strlen(response));
    return;
  }

  size_t path_size = strlen(WEBROOT) + strlen(request.path);
  char path[path_size + 1];
  strcpy(path, WEBROOT);
  strcat(path, request.path);
  path[path_size] = 0;
  printf("Reading file %s\n", path);
  FILE *fptr = fopen(path, "rb");

  if (fptr == NULL) {
    char *msg = "Could not read file ";
    size_t buf_size = strlen(msg) + strlen(path);
    char buf[buf_size + 1];
    strcpy(buf, msg);
    strcat(buf, path);
    buf[buf_size] = 0;
    ulogger_log(LOG_WARN, buf);
    char *response = "HTTP/1.1 404 Not Found\r\n\r\n\r\n";
    write(socket, response, strlen(response));
    return;
  };

  fseek(fptr, 0, SEEK_END);
  long file_size = ftell(fptr);
  rewind(fptr);

  char buffer[file_size];
  fread(buffer, 1, file_size, fptr);
  fclose(fptr);

  char *response = "HTTP/1.1 200 OK\r\n\r\n";
  char full_response[strlen(response) + file_size];
  strcpy(full_response, response);
  memcpy(full_response + strlen(response), buffer, sizeof(buffer));
  printf("Response: %s\n", buffer);
  write(socket, full_response, sizeof(full_response));
  return;
}
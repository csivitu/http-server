/*
 * This program is under GNU general public license v3
 * As a component of the HttpServer project by Josh Chatterjee as part of
 * Forkthis 2024
 */

#include "response.h"
#include "logger.h"
#include "request.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *parseHtml(char *filename) {
  char *response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html; charset=UTF-8\r\n\r\n";

  FILE *fptr = fopen(filename, "rb");

  if (fptr == NULL) {
    perror("Could not read base index.html file");
    exit(EXIT_FAILURE);
  };

  fseek(fptr, 0, SEEK_END);
  long file_size = ftell(fptr);
  rewind(fptr);

  char *buffer = (char *)(malloc(file_size + 1));
  fread(buffer, file_size + 1, 1, fptr);
  fclose(fptr);

  char *full_response = (char *)(malloc(strlen(response) + file_size + 1));
  strcpy(full_response, response);
  strcat(full_response, buffer);
}

char *parseResponse(HandlerFunc handler, char *Input_Buffer, size_t bytes) {

  Request request = ParseRequest(Input_Buffer);
  char *response = handler(request);

  return response;
}
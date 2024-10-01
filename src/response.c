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

char *parseResponse(char *Input_Buffer, size_t bytes) {
  char *response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html; charset=UTF-8\r\n\r\n";

  FILE *fptr = fopen("view/index.html", "rb");

  if (fptr == NULL) {
    perror("Could not read base index.html file");
    exit(EXIT_FAILURE);
  };

  fseek(fptr, 0, SEEK_END);
  long file_size = ftell(fptr);
  rewind(fptr);

  char *buffer = (char *)(malloc(file_size + 1));
  fread(buffer, file_size, 1, fptr); // changed to file_size instead of file_size + 1
  buffer[file_size] = '\0';
  fclose(fptr);

  char *full_response = (char *)(malloc(strlen(response) + file_size + 1));
  if (full_response == NULL) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }
  strcpy(full_response, response);
  strcat(full_response, buffer);  

  ulogger_log(LOG_SUCCESS, "Response: %s", buffer);

  free(buffer);
  return full_response;
}
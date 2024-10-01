
#include "request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Request ParseRequest(char *input_buffer) {
  Request req = {NULL};
  char *line = strtok(input_buffer, "\r\n");

  if (line != NULL) {
    char *method = strtok(line, " ");
    char *path = strtok(NULL, " ");
    if (method != NULL) {
      req.ty = strdup(method);
    }
    if (path != NULL) {
      req.path = strdup(path);
    }
  }

  while ((line = strtok(NULL, "\r\n")) != NULL) {
    if (strncmp(line, "Host:", 5) == 0 && strlen(line) > 6) {
      req.host = strdup(line + 6);
    } else if (strncmp(line, "User-Agent:", 11) == 0 && strlen(line) > 12) {
      req.agent = strdup(line + 12);
    } else if (strncmp(line, "Accept:", 7) == 0 && strlen(line) > 8) {
      req.accept = strdup(line + 8);
    } else if (strncmp(line, "Accept-Language:", 16) == 0 &&
               strlen(line) > 17) {
      req.language = strdup(line + 17);
    } else if (strncmp(line, "Accept-Encoding:", 16) == 0 &&
               strlen(line) > 17) {
      req.encoding = strdup(line + 17);
    } else if (strncmp(line, "Connection:", 11) == 0 && strlen(line) > 12) {
      req.connection = strdup(line + 12);
    }
  }

  return req;
}

#pragma once

typedef struct request {
  char *ty;
  char *path;
  char *host;
  char *agent;
  char *accept;
  char *language;
  char *encoding;
  char *connection;
} Request;

Request ParseRequest(char *input_buffer);
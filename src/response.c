/*
 * This program is under GNU general public license v3
 * As a component of the HttpServer project by Josh Chatterjee as part of
 * Forkthis 2024
 */

#include "response.h"
#include <stdlib.h>
#include "logger.h"

char *parseResponse(char *Input_Buffer, size_t bytes) {
  char *response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: application/json; charset=UTF-8\r\n\r\n"
                   "{\"message\":\"HELLO FROM THE SERVER\"}\n";
  ulogger_log(LOG_SUCCESS, "Response: %s", "HELLO FROM THE SERVER");
  return response;
}

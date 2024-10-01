/*
 * This program is under GNU general public license v3
 * As a component of the HttpServer project by Josh Chatterjee as part of
 * Forkthis 2024
 */
#pragma once
#include <stdlib.h>
#include "request.h"
#include "server.h"
char *parseResponse(HandlerFunc handler, char *Input_Buffer, size_t bytes);
char *parseHtml(char* filename);
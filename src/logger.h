#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

typedef enum {
    LOG_DBG,
    LOG_SUCCESS,
    LOG_WARN,
    LOG_ERR,
    LOG_LEVEL_LEN
} LOG_LEVEL;

#ifdef __EMSCRIPTEN
    #define NO_ANSI
#endif

void ulogger_log(LOG_LEVEL level, const char * fmt, ...);
void ulogger_init(const char *filename);
void ulogger_close();

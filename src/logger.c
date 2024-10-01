#include "logger.h"

static const char *type[LOG_LEVEL_LEN] = {
    "DEBUG",
    "SUCCESS",
    "WARN",
    "ERR"
};

static const char *colors[LOG_LEVEL_LEN] = {
    "\x1b[0m",      // Default
    "\x1b[32m",     // Success
    "\x1b[1;33m",   // Warn
    "\x1b[31m"      // Error
};

static time_t current_time;
static struct tm *m_time;
static FILE *log_file = NULL;

static void get_time() {
    time(&current_time);
    m_time = localtime(&current_time);
}

void ulogger_init(const char *filename) {
    log_file = fopen(filename, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }
}

void ulogger_close() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

void ulogger_log(LOG_LEVEL level, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    get_time();

    #ifndef NO_ANSI 
        printf("%s", colors[level]);
    #endif

    printf("[%02d/%02d/%04d -> %02d:%02d:%02d][%s] ", 
        m_time->tm_mday,
        m_time->tm_mon + 1, 
        m_time->tm_year + 1900,
        m_time->tm_hour, 
        m_time->tm_min, 
        m_time->tm_sec,
        type[level]
    );

    // Log to file
    if (log_file) {
        fprintf(log_file, "[%02d/%02d/%04d -> %02d:%02d:%02d][%s] ", 
            m_time->tm_mday,
            m_time->tm_mon + 1,
            m_time->tm_year + 1900,
            m_time->tm_hour, 
            m_time->tm_min, 
            m_time->tm_sec,
            type[level]
        );
        fflush(log_file);
    }

    vfprintf(stdout, fmt, args);
    printf("\n%s", colors[LOG_DBG]);

    if (log_file) {
        vfprintf(log_file, fmt, args);
        fprintf(log_file, "\n");
        fflush(log_file);
    }
    va_end(args);
}

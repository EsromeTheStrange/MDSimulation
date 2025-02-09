#ifndef MD_LOGGER
#define MD_LOGGER

#include <stdio.h>
#include <stdarg.h>

#define COLOR_DEFAULT   "\x1B[0m"
#define COLOR_GREEN     "\x1B[32m"
#define COLOR_YELLOW    "\x1B[33m"
#define COLOR_BLUE      "\x1B[36m"

void log_important(const char* message){
    printf("%s%s%s", COLOR_YELLOW, message, COLOR_DEFAULT);
}

void log_header(const char* message){
    printf("%s%s%s", COLOR_BLUE, message, COLOR_DEFAULT);
}

void log_success(const char* message){
    printf("%s%s%s", COLOR_GREEN, message, COLOR_DEFAULT);
}
#endif
#ifndef loggerheader
#define loggerheader

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define stdout_red 0
#define stdout_green 1
#define stdout_yellow 2
#define stdout_blue 3
#define stdout_magenta 4
#define stdout_cyan 5
#define stdout_white 6
#define stdout_default 7

#define warning stdout_yellow
#define serious_warning stdout_green
#define error stdout_red

typedef unsigned int logger_warning_type;

static const char *logger_colors[8] = {/*stdout_red*/ "\x1B[31m",
                                       /*stdout_green*/ "\x1B[32m",
                                       /*stdout_yellow*/ "\x1B[33m",
                                       /*stdout_blue*/ "\x1B[34m",
                                       /*stdout_magenta*/ "\x1B[35m",
                                       /*stdout_cyan*/ "\x1B[36m",
                                       /*stdout_white*/ "\x1B[37m",
                                       /*stdout_default*/ "\x1B[0m"};

/**
 * @brief log events with a warning level (which is basically a wrapper for
 * colors) and fmt text
 *
 * @param warning_level basically color
 * @param log text
 * @param ... fmt
 */
void logger_log(logger_warning_type warning_level, const char *log, ...);

/**
 * @brief flush buffers
 *
 */
void logger_flush();

#endif
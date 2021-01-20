#include "logger.h"

void logger_log(logger_warning_type warning_level, const char *log, ...) {
  assert(warning_level >= 0 && warning_level <= 7);

  va_list args;
  va_start(args, log);

  char *log_extra_text = NULL;

  switch (warning_level) {
  case warning:
  case serious_warning:
    log_extra_text = "[warning]";
    break;

  case error:
    log_extra_text = "[error]";
    break;

  default:
    log_extra_text = "[log]";
    break;
  };

  printf("%s%s %s", logger_colors[warning_level], log_extra_text,
         logger_colors[stdout_default]);

  vprintf(log, args);

  va_end(args);
}

void logger_flush() {
  fclose(stdin);
  fclose(stdout);
}
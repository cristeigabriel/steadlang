#ifndef krateheader
#define krateheader

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lexer.h"
#include "../tokenizer.h"

#include "../../vendor/vector.h"

struct _krate_scope {};

struct _krate_settings {
  /**
   * @brief log on mismatch in instance counter and instance files size
   *
   */
  bool file_succesfully_parsed_counter_log;

  /**
   * @brief file_succesfully_parsed_counter error/log level/color
   *
   */
  logger_warning_type file_parsed_passed_size_mismatch;
};

struct _krate_instance {
  /**
   * @brief files to lex and create scopes for
   *
   */
  char **files;

  /**
   * @brief krate system settings
   *
   */
  struct _krate_settings krate_settings;

  /**
   * @brief lexer instance to lex krate prototyping
   *
   */
  struct _lexer_instance **lexer;

  /**
   * @brief krate file counter
   *
   */
  vec_size_t counter;
};

bool krate_initialize(struct _krate_instance *instance);

void krate_release_bunch(struct _krate_instance *instance);

#endif
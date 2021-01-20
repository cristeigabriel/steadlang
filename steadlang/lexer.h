#ifndef lexerheader
#define lexerheader

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/filehelpers.h"
#include "../utils/logger.h"

typedef unsigned int lexer_size_type;

struct _lexer_settings {
  /**
   * @brief the expected extension of passed file
   *
   */
  char *file_expected_extension;

  /**
   * @brief check if file_size > read_size
   *
   */
  bool file_read_safety;

  /**
   * @brief level of error/logger color for extension mismatch
   *
   * if it's set to error, and there's a mismatch, lexer_initialize will fail
   *
   */
  logger_warning_type file_extension_mismatch;
};

struct _lexer_instance {
  /**
   * @brief parsed output from initialization
   *
   */
  char *file;

  /**
   * @brief set of settings for an instance
   *
   */
  struct _lexer_settings lexer_settings;
};

/**
 * @brief initialize instance accordingly
 *
 * @param instance our instance
 * @param filename our file's name
 *
 * @return bool state of initialization
 */
bool lexer_initialize(struct _lexer_instance *instance, const char *filename);

#endif
#ifndef lexerheader
#define lexerheader

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/filehelpers.h"
#include "../utils/logger.h"

struct _tokenizer_settings;
struct _tokenizer_structure;
struct _tokenizer_instance;

extern int errno;

typedef long long lexer_size_type;

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
  bool file_read_safety_log;

  /**
   * @brief level of error/logger color for file/read mismatches
   *
   * if it's set to error, and there's a mismatch, lexer_initialize will fail
   *
   */
  logger_warning_type file_read_sizes_mismatch;

  /**
   * @brief logs and exits when file_size > LLONG_MAX if set to true
   *
   */
  bool file_size_too_big_error;

  /**
   * @brief level of error/logger color for extension mismatch
   *
   * ditto
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

  /**
   * @brief tokenizer instance to analyze file structure
   *
   */
  struct _tokenizer_instance *tokenizer_instance;
};

bool lexer_initialize(struct _lexer_instance *instance,
                      struct _tokenizer_settings tokenizer_settings,
                      const char *filename);

void lexer_release_bunch(struct _lexer_instance *instance);

#endif
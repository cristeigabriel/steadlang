#ifndef tokenizerheader
#define tokenizerheader

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../vendor/vector.h"

#include "../utils/logger.h"

#include "lexer.h"

struct _tokenizer_settings {
  /**
   * @brief krate system identifier
   *
   */
  char *krate;

  /**
   * @brief scope system identifier
   *
   */
  char *scope;

  /**
   * @brief scope system delimiter
   *
   */
  char *scope_delimiter;
};

struct _tokenizer_instance {
  /**
   * @brief lexer instance to get lexed file
   *
   */
  struct _lexer_instance *lexer;

  /**
   * @brief tokenizer settings for delimiters/identifiers
   *
   */
  struct _tokenizer_settings tokenizer_settings;
};

/**
 * @brief make an instance that tokenizes the lexer instance lexed file
 * according to tokenizer_settings
 *
 * @param instance tokenizer instance to initialize
 * @return bool state of initialization
 */
bool tokenizer_initialize(struct _tokenizer_instance *instance);

#endif
#ifndef tokenizerheader
#define tokenizerheader

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../vendor/vector.h"

#include "../utils/logger.h"

struct _lexer_instance;
struct _lexer_settings;

struct _tokenizer_settings {
  char *krate;
  char *scope;
  char *scope_opener;
  char *scope_ender;
  char *scope_return_type_delimiter;
  char *arglist_opener;
  char *arglist_ender;
  char *argument_type_delimiter;
};

struct _tokenizer_structure {
  char **scopes;
  char **scope_types;
  char **scope_arguments;
  char **scope_argument_types;
};

struct _tokenizer_instance {
  /**
   * @brief tokenizer lexer instance to get file
   *
   */
  struct _lexer_instance *lexer_instance;
  /**
   * @brief tokenizer settings for delimiters/identifiers
   *
   */
  struct _tokenizer_settings tokenizer_settings;

  /**
   * @brief tokenizer structure to add contained stuff
   *
   */
  struct _tokenizer_structure tokenizer_structure;
};

bool tokenizer_initialize(struct _tokenizer_instance *instance);

void tokenizer_release_bunch(struct _tokenizer_instance *instance);

#endif
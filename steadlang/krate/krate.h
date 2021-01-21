#ifndef krateheader
#define krateheader

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lexer.h"
#include "../tokenizer.h"

#include "../../vendor/vector.h"

static bool krate_passed_files_check = false;

struct _krate_scope {};

struct _krate_instance {
  /**
   * @brief files to lex and create scopes for
   *
   */
  char **files;

  /**
   * @brief lexer instance to lex krate prototyping
   *
   */
  struct _lexer_instance **lexer;
};

bool krate_initialize(struct _krate_instance *instance);
void krate_release_bunch(struct _krate_instance *instance);

#endif
#include "tokenizer.h"
#include "lexer.h"

static bool tokenizer_reach_scope_initialize = false;

bool tokenizer_initialize(struct _tokenizer_instance *instance) {
  tokenizer_reach_scope_initialize = false;

  if (instance == NULL) {
    logger_log(error,
               "failed to initialize tokenizer instance (%p), returned NULL\n",
               &instance);
    return false;
  }

  instance->tokenizer_structure.scopes = vector_create();

  tokenizer_reach_scope_initialize = true;

  if (instance->tokenizer_structure.scopes != NULL) {
    char *file_copy;
    memcpy(&file_copy, &instance->lexer_instance->file,
           sizeof(instance->lexer_instance->file));

    char *scope = strtok(file_copy, instance->tokenizer_settings.scope_opener);

    while (scope != NULL) {
      vector_add(&instance->tokenizer_structure.scopes, scope);
      scope = strtok(NULL, instance->tokenizer_settings.scope);
    }
  }

  return true;
}

void tokenizer_release_bunch(struct _tokenizer_instance *instance) {
  if (tokenizer_reach_scope_initialize) {
    vector_free(instance->tokenizer_structure.scopes);
  }
}
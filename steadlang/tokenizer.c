#include "tokenizer.h"

bool tokenizer_initialize(struct _tokenizer_instance *instance) {
  if (instance == NULL) {
    logger_log(error,
               "failed to initialize tokenizer instance (%p), returned NULL\n",
               &instance);
    return false;
  }

  if (instance->lexer->file == NULL) {
    logger_log(error, "failed getting tokenizer file (%p), returned NULL\n",
               &instance->lexer->file);
    return false;
  }

  return true;
}
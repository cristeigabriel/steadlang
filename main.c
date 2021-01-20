#include "main.h"

int main(int argc, char **argv) {
  if (argc > 2 || argc < 2 || argv[1] == NULL) {
    logger_log(error, "you must pass a file to interpret. there's currently no "
                      "live interpreting, proceed to do:\n./stead [file]\n");
    return 0;
  }

  struct _lexer_settings lexer_settings;
  lexer_settings.file_expected_extension = ".sl";
  lexer_settings.file_extension_mismatch = warning;
  lexer_settings.file_read_safety = true;
  lexer_settings.file_read_sizes_mismatch = error;
  lexer_settings.file_size_too_big_error = true;

  struct _lexer_instance *lexer_instance =
      (struct _lexer_instance *)malloc(sizeof(struct _lexer_instance));

  if (lexer_instance == NULL) {
    logger_log(error,
               "failed to initialize lexer instance (%p), returned NULL\n",
               &lexer_instance);
    return 0;
  }

  lexer_instance->lexer_settings = lexer_settings;

  struct _tokenizer_settings tokenizer_settings;
  tokenizer_settings.krate = "krate";
  tokenizer_settings.scope = "scope";
  tokenizer_settings.scope_delimiter = "::";

  struct _tokenizer_instance *tokenizer_instance =
      (struct _tokenizer_instance *)malloc(sizeof(struct _tokenizer_instance));

  if (tokenizer_instance == NULL) {
    logger_log(error,
               "failed to initialize tokenizer instance (%p), returned NULL\n",
               &tokenizer_instance);
    return 0;
  }

  tokenizer_instance->tokenizer_settings = tokenizer_settings;
  tokenizer_instance->lexer = lexer_instance;

  if (lexer_initialize(lexer_instance, argv[1]))
    printf("%s\n", lexer_instance->file);
  else {
    logger_log(error, "lexer initializer returned false\n");
    return 0;
  }

  if (tokenizer_initialize(tokenizer_instance))
    ;
  else {
    logger_log(error, "tokenizer initializer returned false");
    return 0;
  }

  free(lexer_instance->file);
  free(lexer_instance);
  free(tokenizer_instance);
  logger_flush();

  return 0;
}
#include "main.h"

int main(int argc, char **argv) {
  if (argc > 2 || argc < 2 || argv[1] == NULL) {
    logger_log(error, "you must pass a file to interpret. there's currently no "
                      "live interpreting, proceed to do:\n./stead [file]\n");
    return 0;
  }

  struct _lexer_instance *lexer_instance =
      (struct _lexer_instance *)malloc(sizeof(struct _lexer_instance));

  struct _krate_instance *krate_instance =
      (struct _krate_instance *)malloc(sizeof(struct _krate_instance));

  if (lexer_instance == NULL) {
    logger_log(error,
               "failed to initialize lexer instance (%p), returned NULL\n",
               &lexer_instance);
    goto destruct;
  }

  if (krate_instance == NULL) {
    logger_log(error,
               "failed to initialize krate instance (%p), returned NULL\n",
               &krate_instance);
    goto destruct;
  }

  struct _lexer_settings lexer_settings;
  lexer_settings.file_expected_extension = ".sl";
  lexer_settings.file_extension_mismatch = warning;
  lexer_settings.file_read_safety_log = true;
  lexer_settings.file_read_sizes_mismatch = error;
  lexer_settings.file_size_too_big_error = true;

  lexer_instance->lexer_settings = lexer_settings;

  struct _tokenizer_settings tokenizer_settings;
  tokenizer_settings.krate = "krate";
  tokenizer_settings.scope = "scope";
  tokenizer_settings.scope_opener = "{";
  tokenizer_settings.scope_ender = "}";
  tokenizer_settings.scope_return_type_delimiter = "->";
  tokenizer_settings.arglist_opener = "(";
  tokenizer_settings.arglist_ender = ")";
  tokenizer_settings.argument_type_delimiter = ":";

  struct _krate_settings krate_settings;
  krate_settings.file_succesfully_parsed_counter_log = true;
  krate_settings.file_parsed_passed_size_mismatch = warning;

  krate_instance->krate_settings = krate_settings;
  krate_instance->files = vector_create();

  // vector_add(&krate_instance->files, "test.slk");
  // vector_add(&krate_instance->files, "test.slk");
  // vector_add(&krate_instance->files, "test.slc");

  if (lexer_initialize(lexer_instance, tokenizer_settings, argv[1]))
    ;
  else {
    logger_log(error, "lexer initializer returned false\n");
    goto destruct;
  }

  if (krate_initialize(krate_instance))
    logger_log(stdout_blue, "%s\n", krate_instance->lexer[0]->file);
  else {
    logger_log(error, "krate initializer returned false\n");
    goto destruct;
  }

destruct:
  lexer_release_bunch(lexer_instance);
  free(lexer_instance);
  krate_release_bunch(krate_instance);
  free(krate_instance);
  logger_flush();

  return 0;
}
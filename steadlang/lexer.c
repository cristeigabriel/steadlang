#include "lexer.h"
#include "tokenizer.h"

static bool lexer_reached_file_initialization = false;
static bool lexer_reached_tokenizer_initialization = false;

bool lexer_initialize(struct _lexer_instance *instance,
                      struct _tokenizer_settings tokenizer_settings,
                      const char *filename) {
  lexer_reached_file_initialization = false;
  lexer_reached_tokenizer_initialization = false;

  if (instance == NULL) {
    logger_log(error,
               "failed to initialize lexer instance (%p), returned NULL\n",
               &instance);
    return false;
  }

  const char *extension = filehelpers_get_extension(filename);
  if (strcmp(extension, instance->lexer_settings.file_expected_extension) !=
          0 &&
      strcmp(extension, "") != 0) {
    logger_log(instance->lexer_settings.file_extension_mismatch,
               "file extension is not '%s' but '%s'\n",
               instance->lexer_settings.file_expected_extension, extension);
    if (instance->lexer_settings.file_extension_mismatch == error)
      return false;
  }

  FILE *file = NULL;
  file = fopen(filename, "r");

  if (!file) {
    logger_log(error, "failed reading file %s\n", filename);
    return false;
  }

  if (file) {
    lexer_size_type file_size = 0, read_size = 0;

    if (fseek(file, 0, SEEK_END) == -1) {
      logger_log(error,
                 "failed at fseek, perhaps file is unseekable? errno: %d\n",
                 errno);
      return false;
    }

    file_size = ftell(file);
    if (file_size == -1) {
      logger_log(error, "failed at ftell, returned -1\n");
      return false;
    }

    if (file_size > LLONG_MAX &&
        instance->lexer_settings.file_size_too_big_error) {
      logger_log(error, "file size bigger than LLONG_MAX (%lld)\n", LLONG_MAX);
      return false;
    }

    rewind(file);

    instance->file = (char *)malloc(sizeof(char) * (file_size + 1));
    lexer_reached_file_initialization = true;

    read_size = fread(instance->file, sizeof(char), file_size, file);
    if (read_size == 0) {
      logger_log(error, "failed at fread, returned 0\n");
      return false;
    }

    instance->file[file_size] = '\0';

    if (file_size != read_size &&
        instance->lexer_settings.file_read_safety_log) {
      logger_log(instance->lexer_settings.file_read_sizes_mismatch,
                 "failed reading entirety of %s\n", filename);

      if (instance->lexer_settings.file_read_safety_log &&
          instance->lexer_settings.file_read_sizes_mismatch == error)
        return false;
    }

    if (fclose(file) == EOF) {
      logger_log(error, "failed at fclose, returned EOF (-1)\n");
      return false;
    }
  }

  if (file != NULL) {
    instance->tokenizer_instance = (struct _tokenizer_instance *)malloc(
        sizeof(struct _tokenizer_instance));

    lexer_reached_tokenizer_initialization = true;

    if (instance->tokenizer_instance == NULL) {
      logger_log(error,
                 "failed to get tokenizer instance (%p), returned NULL\n",
                 &instance->tokenizer_instance);
      return false;
    }

    instance->tokenizer_instance->lexer_instance = instance;

    if (tokenizer_initialize(instance->tokenizer_instance)) {
      instance->tokenizer_instance->tokenizer_settings = tokenizer_settings;

      for (vec_size_t i = 0;
           i < vector_size(
                   instance->tokenizer_instance->tokenizer_structure.scopes);
           ++i) {
        logger_log(stdout_blue, "%d: %s\n", i,
                   instance->tokenizer_instance->tokenizer_structure.scopes[i]);
      }

    } else {
      logger_log(error, "tokenizer initializer returned false\n");
      return false;
    }
  }

  return true;
}

void lexer_release_bunch(struct _lexer_instance *instance) {
  if (lexer_reached_file_initialization) {
    free(instance->file);
  }

  if (lexer_reached_tokenizer_initialization) {
    free(instance->tokenizer_instance);
  }
}
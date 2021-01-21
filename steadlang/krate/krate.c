#include "krate.h"

bool krate_initialize(struct _krate_instance *instance) {
  if (instance == NULL) {
    logger_log(error,
               "failed to initialize krate instance (%p), returned NULL\n",
               &instance);
    return false;
  }

  if (vector_size(instance->files) == 0) {
    logger_log(error, "no files passed to krate instance\n");
    return false;
  }

  krate_passed_files_check = true;

  struct _lexer_settings krate_lexer_settings;
  krate_lexer_settings.file_expected_extension = ".slk";
  krate_lexer_settings.file_extension_mismatch = error;
  krate_lexer_settings.file_read_safety = true;
  krate_lexer_settings.file_read_sizes_mismatch = error;
  krate_lexer_settings.file_size_too_big_error = true;

  instance->lexer = vector_create();

  for (vec_size_t i = 0; i < vector_size(instance->files); ++i) {
    vector_add(&instance->lexer, (struct _lexer_instance *)malloc(
                                     sizeof(struct _lexer_instance)));

    instance->lexer[i]->lexer_settings = krate_lexer_settings;

    lexer_initialize(instance->lexer[i], instance->files[i]);

    const char *extension = filehelpers_get_extension(instance->files[i]);
    if (strcmp(extension,
               instance->lexer[i]->lexer_settings.file_expected_extension) !=
            0 &&
        strcmp(extension, "") != 0) {
      logger_log(instance->lexer[i]->lexer_settings.file_extension_mismatch,
                 "file extension is not '%s' but '%s'\n",
                 instance->lexer[i]->lexer_settings.file_expected_extension,
                 extension);
      if (instance->lexer[i]->lexer_settings.file_extension_mismatch == error)
        return false;
    }

    printf("%s\n", instance->lexer[i]->file);
  }
}

void krate_release_bunch(struct _krate_instance *instance) {
  if (krate_passed_files_check) {
    for (vec_size_t i = 0; i < vector_size(instance->lexer); ++i) {
      free(instance->lexer[i]->file);
    }

    free(*instance->lexer);
    vector_free(instance->files);
  }
}
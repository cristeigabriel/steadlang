#include "krate.h"

bool krate_initialize(struct _krate_instance *instance) {
  // to allow multiple reinitializations which will eventually
  // also need freeing, and with our method it can only be done iin
  // this way 'properly' as we need
  krate_passed_files_check = false;
  krate_passed_extension_check = false;

  instance->counter = 0;

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

  struct _lexer_settings krate_lexer_settings;
  krate_lexer_settings.file_expected_extension = ".slk";
  krate_lexer_settings.file_extension_mismatch = error;
  krate_lexer_settings.file_read_safety_log = true;
  krate_lexer_settings.file_read_sizes_mismatch = error;
  krate_lexer_settings.file_size_too_big_error = true;

  instance->lexer = vector_create();

  static bool passed_counter_once = false;
  passed_counter_once = false;
  for (vec_size_t i = 0; i < vector_size(instance->files); ++i) {
    vector_add(&instance->lexer, (struct _lexer_instance *)malloc(
                                     sizeof(struct _lexer_instance)));

    instance->lexer[i]->lexer_settings = krate_lexer_settings;

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
        continue;
    } else {
      krate_passed_extension_check = true;
      instance->counter++;
      passed_counter_once = true;
    }

    if (lexer_initialize(instance->lexer[i], instance->files[i])) {
      krate_passed_files_check = true;
      if (!passed_counter_once) {
        instance->counter++;
        passed_counter_once = true;
      }
    } else {
      logger_log(error, "lexer initializer returned false\n");
      krate_passed_files_check = true;
      continue;
    }
  }

  if (instance->krate_settings.file_succesfully_parsed_counter_log)
    logger_log(instance->krate_settings.file_parsed_passed_size_mismatch,
               "krate: counted: %ld, passed: %ld\n", instance->counter,
               vector_size(instance->files));

  if (instance->counter != vector_size(instance->files) &&
      instance->krate_settings.file_succesfully_parsed_counter_log &&
      instance->krate_settings.file_parsed_passed_size_mismatch == error)
    return false;
}

void krate_release_bunch(struct _krate_instance *instance) {
  if (krate_passed_files_check) {
    // memory leak, to fix
    // for (vec_size_t i = 0; i < vector_size(instance->lexer); ++i) {
    //   if (i < instance->counter) {
    //     free(instance->lexer[i]->file);
    //   }
    // }
  }

  if (krate_passed_extension_check) {
    free(*instance->lexer);
    vector_free(instance->files);
  }
}
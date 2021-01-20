#include "lexer.h"

bool lexer_initialize(struct _lexer_instance *instance, const char *filename) {
  const char *extension = filehelpers_get_extension(filename);
  if (extension != instance->lexer_settings.file_expected_extension) {
    logger_log(instance->lexer_settings.file_extension_mismatch,
               "file extension is not '%s' but '%s'\n",
               instance->lexer_settings.file_expected_extension, extension);
    if (instance->lexer_settings.file_extension_mismatch == error)
      return false;
  }

  if (instance == NULL) {
    logger_log(error, "failed getting instance (%p)\n", &instance);
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

    fseek(file, 0, SEEK_END);

    file_size = ftell(file);
    rewind(file);

    instance->file = (char *)malloc(sizeof(char) * (file_size + 1));
    read_size = fread(instance->file, sizeof(char), file_size, file);

    instance->file[file_size] = '\0';

    if (file_size != read_size && instance->lexer_settings.file_read_safety) {
      logger_log(serious_warning, "failed reading entirety of %s\n", filename);
      free(instance);

      return false;
    }

    fclose(file);
  }

  return true;
}
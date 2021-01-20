#include "main.h"

int main(int argc, char **argv) {
  if (argc > 2 || argc < 2 || argv[1] == NULL) {
    logger_log(error, "you must pass a file to interpret. there's currently no "
                      "live interpreting, proceed to do:\n./stead [file]\n");
    return 0;
  }

  logger_log(stdout_blue, "%d\n", argc);
  logger_log(stdout_cyan, "hi\n");
  logger_log(stdout_red, "how\n");
  logger_log(error, "hello there\n");
  logger_log(error, "yo\n");

  struct _lexer_settings settings;
  settings.file_expected_extension = ".sl";
  settings.file_read_safety = true;
  settings.file_extension_mismatch = serious_warning;

  struct _lexer_instance *instance =
      (struct _lexer_instance *)malloc(sizeof(struct _lexer_instance));

  if (instance == NULL) {
    logger_log(error, "failed to initialize instance (%p)\n", &instance);
    return 0;
  }

  instance->lexer_settings = settings;

  if (lexer_initialize(instance, argv[1]))
    printf("%s\n", instance->file);
  else
    logger_log(error, "lexer failed to initialize\n");

  free(instance);
  logger_flush();

  return 0;
}
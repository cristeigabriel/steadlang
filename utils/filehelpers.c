#include "filehelpers.h"

const char *filehelpers_get_extension(const char *filename) {
  // i.e.: .a, .b, .c, but we can't just have a . file
  assert(filename && strlen(filename) > 1);
  if (!strstr(filename, "."))
    return "";

  return strrchr(filename, '.');
}

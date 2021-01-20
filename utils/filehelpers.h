#ifndef filehelpersheader
#define filehelpersheader

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief get file extension in '.extension' format
 *
 * @param filename file name (including extension)
 * @return const char* file extension in '.extension' format
 */
const char *filehelpers_get_extension(const char *filename);

#endif
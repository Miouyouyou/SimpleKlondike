#ifndef MYY_INCLUDE_FILE_HELPERS
#define MYY_INCLUDE_FILE_HELPERS 1

#include <stdint.h>

unsigned int fh_ReadFileToBuffer
(const char * restrict const name,
 void * restrict const buffer,
 const unsigned int size);

unsigned int fh_ReadFileToStringBuffer
(const char * restrict const name,
 void * restrict const buffer,
 const unsigned int size);

/** Copy the whole file contents into buffer, using the AssetsManager
 *
 * ASSUMPTIONS :
 * - There's a publicly available AssetsManager address identified by
 *   myy_assets_manager.
 * - 'buffer' can contain the whole file
 *
 * CAUTION :
 * If there's not enough space in buffer, this procedure will most
 * likely generate a SIGSEGV or, worse, corrupt the memory.
 *
 * PARAMS :
 * @param filepath The file's path in the Assets archive.
 * @param buffer   The buffer to store the file's content in.
 *
 * RETURNS :
 * 1 if the whole copy was done successfully
 * 0 otherwise
 */
unsigned int fh_WholeFileToBuffer
(const char * restrict const filepath,
 void * restrict const buffer);

#endif

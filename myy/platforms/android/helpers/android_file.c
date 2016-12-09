/*
 * Author: Miouyouyou (Myy)
 *
 * Copyright: Miouyouyou (Myy)
 *
 * LICENSE: BSD 2-Clause
 *
 */

#include <helpers/file.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

extern AAssetManager *myy_assets_manager;

unsigned int fh_WholeFileToBuffer
(const char * restrict const filepath,
 void * restrict const buffer) {
  /* Couldn't they mount the whole archive as a filesystem ? */
  AAsset *file =
    AAssetManager_open(myy_assets_manager, filepath,
                       AASSET_MODE_STREAMING);
  unsigned int
    file_size = AAsset_getLength(file),
    read_bytes = AAsset_read(file, buffer, file_size);

  AAsset_close(file);
  return read_bytes == file_size;
}


unsigned int fh_ReadFileToBuffer
(const char * restrict const filepath,
 void * restrict const buffer,
 const unsigned int size) {
  AAsset *file =
    AAssetManager_open(myy_assets_manager, filepath,
                       AASSET_MODE_STREAMING);

  unsigned int
    read_bytes = AAsset_read(file, buffer, size);

  AAsset_close(file);

  return read_bytes;
}

unsigned int fh_ReadFileToStringBuffer
(const char * restrict const filepath,
 void * restrict const buffer,
 const unsigned int size) {
  unsigned int read_bytes =
    fh_ReadFileToBuffer(filepath, buffer, size);
  ((uint8_t *) buffer)[read_bytes] = '\0';
  return read_bytes;
}

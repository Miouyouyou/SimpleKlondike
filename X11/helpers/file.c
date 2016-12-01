#include <helpers/file.h>

/* read - close */
#include <unistd.h>

/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

unsigned int fh_WholeFileToBuffer
(const char * restrict const filepath,
 void * restrict const buffer) {

  ssize_t bytes_read;
  off_t file_size;
  struct stat fd_stats;

  int fd = open(filepath, O_RDONLY);

  if (fd != -1) {

    fstat(fd, &fd_stats);

    file_size = fd_stats.st_size;

    bytes_read = read(fd, buffer, file_size);
    close(fd);

    return bytes_read == file_size;

  }
  else return 0;
}

unsigned int fh_ReadFileToBuffer
(const char * restrict const name, 
 void * restrict const buffer, 
 const unsigned int size) {

  int fd = open(name, O_RDONLY);
  int bytes_read = read(fd, buffer, size);
  close(fd);
  return bytes_read;

}

unsigned int fh_ReadFileToStringBuffer
(const char * restrict const name, 
 void * restrict const buffer, 
 const unsigned int size) {

  unsigned int bytes_read = fh_ReadFileToBuffer(name, buffer, size);
  ((uint8_t *) buffer)[bytes_read] = 0;
  return bytes_read;

}


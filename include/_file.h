#ifndef __FILE_H_
#define __FILE_H_

#include "_int.h"
typedef long long int __off64_t;
typedef int __off_t;

#define O_RDWR 02
#define O_CREAT 0100
#define O_RDONLY 00
#define O_APPEND 02000
#define O_WRONLY 01
#define O_TRUNC 01000

/* mode_t types */
typedef unsigned int mode_t;
#define S_IRWXU 00700  // user
#define S_IRUSR 00400
#define S_IWUSR 00200
#define S_IXUSR 00100
#define S_IRWXG 00070
#define S_IRGRP 00040
#define S_IWGRP 00020
#define S_IXGRP 00010
#define S_IRWXO 00007
#define S_IROTH 00004
#define S_IWOTH 00002
#define S_IXOTH 00001
#define S_ISUID 0004000
#define S_ISGID 0002000
#define S_ISVTX 0001000

/* return a file descriptor of a file at pathname with flags */
int _open(const char *pathname, int flags) __attribute__((nonnull(1)));

/* return a file descriptor of a created file at pathname with modes */
int _creat(const char *pathname, mode_t mode) __attribute__((nonnull(1)));
;

int _openat(int dirfd, const char *pathname, int flags, ...
            /* mode_t mode */) __attribute__((nonnull(2)));

/* close fd */
int _close(int fd);

/* FILE*  copied from libc  */

struct _IO_FILE;

struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;

/* During the build of glibc itself, _IO_lock_t will already have been
   defined by internal headers.  */
#ifndef _IO_lock_t_defined
typedef void _IO_lock_t;
#endif

/* The tag name of this struct is _IO_FILE to preserve historic
   C++ mangled names for functions taking FILE* arguments.
   That name should not be used in new code.  */
struct _IO_FILE {
    int _flags; /* High-order word is _IO_MAGIC; rest is flags. */

    /* The following pointers correspond to the C++ streambuf protocol. */
    char *_IO_read_ptr;   /* Current read pointer */
    char *_IO_read_end;   /* End of get area. */
    char *_IO_read_base;  /* Start of putback+get area. */
    char *_IO_write_base; /* Start of put area. */
    char *_IO_write_ptr;  /* Current put pointer. */
    char *_IO_write_end;  /* End of put area. */
    char *_IO_buf_base;   /* Start of reserve area. */
    char *_IO_buf_end;    /* End of reserve area. */

    /* The following fields are used to support backing up and undo. */
    char *_IO_save_base;   /* Pointer to start of non-current get area. */
    char *_IO_backup_base; /* Pointer to first valid character of backup area */
    char *_IO_save_end;    /* Pointer to end of non-current get area. */

    struct _IO_marker *_markers;

    struct _IO_FILE *_chain;

    int _fileno;
    int _flags2;
    __off_t _old_offset; /* This used to be _offset but it's too small.  */

    /* 1+column number of pbase(); 0 is unknown. */
    unsigned short _cur_column;
    signed char _vtable_offset;
    char _shortbuf[1];

    _IO_lock_t *_lock;
#ifdef _IO_USE_OLD_IO_FILE
};

struct _IO_FILE_complete {
    struct _IO_FILE _file;
#endif
    __off64_t _offset;
    /* Wide character stream stuff.  */
    struct _IO_codecvt *_codecvt;
    struct _IO_wide_data *_wide_data;
    struct _IO_FILE *_freeres_list;
    void *_freeres_buf;
    size_t __pad5;
    int _mode;
    /* Make sure we don't get into trouble again.  */
    char _unused2[15 * sizeof(int) - 4 * sizeof(void *) - sizeof(size_t)];
};

#define FILE struct _IO_FILE
#endif

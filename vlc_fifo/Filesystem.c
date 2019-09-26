
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdarg.h>

#include <errno.h>

#include "vlc_common.h"
#include "vlc_fs.h"

#include <assert.h>

#ifndef O_TMPFILE
# define O_TMPFILE 0
#endif



int vlc_open (const char *filename, int flags, ...)
{
    unsigned int mode = 0;
    va_list ap;

    va_start (ap, flags);
    if (flags & (O_CREAT|O_TMPFILE))
        mode = va_arg (ap, unsigned int);
    va_end (ap);

#ifdef O_CLOEXEC
    return open(filename, flags | O_CLOEXEC, mode);
#else
    int fd = open(filename, flags, mode);
    if (fd != -1)
        vlc_cloexec(fd);
    return -1;
#endif
}

int vlc_close (int fd)
{
    int ret;
#ifdef POSIX_CLOSE_RESTART
    ret = posix_close(fd, 0);
#else
    ret = close(fd);
    /* POSIX.2008 (and earlier) does not specify if the file descriptor is
     * closed on failure. Assume it is as on Linux and most other common OSes.
     * Also emulate the correct error code as per newer POSIX versions. */
    if (unlikely(ret != 0) && unlikely(errno == EINTR))
        errno = EINPROGRESS;
#endif
    assert(ret == 0 || errno != EBADF); /* something is corrupt? */
    return ret;
}



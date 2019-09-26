#ifndef VLC_FS_H
#define VLC_FS_H 1

VLC_API int vlc_open(const char *filename, int flags, ...) VLC_USED;
VLC_API int vlc_close(int fd);

#endif

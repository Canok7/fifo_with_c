#include "vlc_common.h"


VLC_API void vlc_testcancel(void);

VLC_API void vlc_mutex_init(vlc_mutex_t *);
VLC_API void vlc_mutex_destroy(vlc_mutex_t *);
VLC_API int vlc_mutex_trylock( vlc_mutex_t * );
VLC_API void vlc_mutex_lock(vlc_mutex_t *);
VLC_API void vlc_mutex_unlock(vlc_mutex_t *);

void vlc_assert_locked (vlc_mutex_t *);

VLC_API void vlc_cond_init(vlc_cond_t *);
VLC_API void vlc_cond_destroy(vlc_cond_t *);
VLC_API void vlc_cond_signal(vlc_cond_t *);
VLC_API void vlc_cond_wait(vlc_cond_t *cond, vlc_mutex_t *mutex);
VLC_API int vlc_cond_timedwait(vlc_cond_t *cond, vlc_mutex_t *mutex,
                               mtime_t deadline);



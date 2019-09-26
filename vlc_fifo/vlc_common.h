#ifndef VLC_COMMON_H
#define VLC_COMMON_H 1

#include <stdlib.h>

#include <string.h>
#include <stdio.h>

#include <pthread.h>


/*-------------------type--------------*/
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
typedef unsigned long   uint64_t;


typedef long int64_t;
typedef int64_t mtime_t;
typedef int bool;



//!!!!!!!!!!!!!!!!!!!!!!!! important 
//#if sizeof(void*) == 8//这个写法错误, sizeof 本身是一个运算符，编译阶段 .......
//#if 1
#if 1
//#pragma message("64bit define!!!!!!!!")
//64bit-system
	typedef  uint64_t     uintptr_t; //uintprt_t 表示一个地址 void *的长度的数据类型，32位用 uint32_t
#else
//32bit-system
	typedef  uint32_t     uintptr_t;
#endif

typedef  int64_t       intmax_t;
typedef uint64_t      uintmax_t;

/* block */
typedef struct block_t      block_t;
typedef struct block_fifo_t block_fifo_t;


#ifndef SIZE_MAX
   #define SIZE_MAX 			  (~(size_t)0)
#endif

/*-------------------type--------------*/


/* Linkage */
#ifdef __cplusplus
#define VLC_EXTERN extern "C"
#else
#define VLC_EXTERN
#endif

#if 0
#define VLC_EXPORT __attribute__((visibility("default")))
#else
#define VLC_EXPORT
#endif

#define VLC_API VLC_EXTERN VLC_EXPORT
#define VLC_UNUSED(x) (void)(x)


#define VLC_DEPRECATED
#define VLC_DEPRECATED_ENUM
#define VLC_FORMAT(x,y)
#define VLC_FORMAT_ARG(x)
#define VLC_MALLOC
#define VLC_USED

#define VLC_TS_INVALID (0)
#define VLC_TS_0 (1)

#define CLOCK_FREQ (1000000)


/* __MAX and __MIN: self explanatory */
#ifndef __MAX
#define __MAX(a, b)   ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef __MIN
#define __MIN(a, b)   ( ((a) < (b)) ? (a) : (b) )
#endif


/*--------------pthread-------------------------------*/
typedef pthread_mutex_t vlc_mutex_t;
typedef pthread_cond_t vlc_cond_t;
#define vlc_cleanup_push( routine, arg ) pthread_cleanup_push (routine, arg)
#define vlc_cleanup_pop( ) pthread_cleanup_pop (0)
/*--------------pthread-------------------------------*/


#ifdef __GNUC__
#define likely(p)     __builtin_expect(!!(p), 1)
#define unlikely(p)   __builtin_expect(!!(p), 0)
#define unreachable() __builtin_unreachable()
#else

//加双 ！！ ,直接把一个数变成了 0 或者1 了。
#define likely(p)     (!!(p))
#define unlikely(p)   (!!(p))
#define unreachable() ((void)0)
#endif

#endif


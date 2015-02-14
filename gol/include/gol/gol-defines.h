#ifndef GOL_DEFINES_H
#define GOL_DEFINES_H

#if !defined(GOL_EXTERN)
# if defined(__cplusplus)
#  define GOL_EXTERN extern "C"
# else
#  define GOL_EXTERN extern
# endif
#endif

#if !defined(GOL_INLINE)
# if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define GOL_INLINE static inline
# elif defined(__cplusplus)
#  define GOL_INLINE static inline
# elif defined(__GNUC__)
#  define GOL_INLINE static __inline__
# else
#  define GOL_INLINE static
# endif
#endif

#endif

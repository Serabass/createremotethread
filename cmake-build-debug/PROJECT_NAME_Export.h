
#ifndef PROJECT_NAME_EXPORT_H
#define PROJECT_NAME_EXPORT_H

#ifdef PROJECT_NAME_BUILT_AS_STATIC
#  define PROJECT_NAME_EXPORT
#  define PROJECT_NAME_NO_EXPORT
#else
#  ifndef PROJECT_NAME_EXPORT
#    ifdef PROJECT_NAME_EXPORTS
        /* We are building this library */
#      define PROJECT_NAME_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define PROJECT_NAME_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef PROJECT_NAME_NO_EXPORT
#    define PROJECT_NAME_NO_EXPORT 
#  endif
#endif

#ifndef PROJECT_NAME_DEPRECATED
#  define PROJECT_NAME_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef PROJECT_NAME_DEPRECATED_EXPORT
#  define PROJECT_NAME_DEPRECATED_EXPORT PROJECT_NAME_EXPORT PROJECT_NAME_DEPRECATED
#endif

#ifndef PROJECT_NAME_DEPRECATED_NO_EXPORT
#  define PROJECT_NAME_DEPRECATED_NO_EXPORT PROJECT_NAME_NO_EXPORT PROJECT_NAME_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PROJECT_NAME_NO_DEPRECATED
#    define PROJECT_NAME_NO_DEPRECATED
#  endif
#endif

#endif /* PROJECT_NAME_EXPORT_H */

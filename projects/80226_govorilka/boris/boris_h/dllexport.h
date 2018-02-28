#ifdef LIBAPP_API
#   undef LIBAPP_API
#endif

#ifdef _WIN32
#   ifdef  LIBAPP_EXPORTS
#       define LIBAPP_API __declspec(dllexport)
#   else
#       define LIBAPP_API __declspec(dllimport)
#   endif
#else
#   define LIBAPP_API
#endif


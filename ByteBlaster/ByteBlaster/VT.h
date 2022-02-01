#ifdef VT_EXPORTS
#define VTAPI __declspec(dllexport) 
#else
#define VTAPI __declspec(dllimport) 
#endif

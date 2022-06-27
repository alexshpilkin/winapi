/* requires windef.h */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GDIAPI
#define GDIAPI DECLSPEC_IMPORT
#endif

typedef struct HBRUSH__ __near *HBRUSH;
typedef struct HDC__    __near *HDC;

/* GetStockObject */

#define WHITE_BRUSH         0
#define LTGRAY_BRUSH        1
#define GRAY_BRUSH          2
#define DKGRAY_BRUSH        3
#define BLACK_BRUSH         4
#define HOLLOW_BRUSH        5
#define NULL_BRUSH          HOLLOW_BRUSH
#define WHITE_PEN           6
#define BLACK_PEN           7
#define NULL_PEN            8
#define OEM_FIXED_FONT      10
#define ANSI_FIXED_FONT     11
#define ANSI_VAR_FONT       12
#define SYSTEM_FONT         13
#define DEVICE_DEFAULT_FONT 14
/* Win16 >= 3.0 */
#define DEFAULT_PALETTE     15
#define SYSTEM_FIXED_FONT   16

GDIAPI void *APIENTRY GetStockObject(int nIndex);

#ifdef __cplusplus
}
#endif

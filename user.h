/* requires windef.h */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef USERAPI
#define USERAPI DECLSPEC_IMPORT
#endif

typedef struct HWND__ __near *HWND;

/* SetLastErrorEx */

#define SLE_ERROR      0x00000001
#define SLE_MINORERROR 0x00000002
#define SLE_WARNING    0x00000003

USERAPI void APIENTRY SetLastErrorEx(uint32_t dwErrCode, uint32_t dwType);

/* MessageBox */

#define MB_TYPEMASK                  0x0000000F
#define MB_ICONMASK                  0x000000F0
#define MB_DEFMASK                   0x00000F00
#define MB_MODEMASK                  0x00003000
#define MB_MISCMASK                  0x0000C000

#define MB_OK                        0x00000000
#define MB_OKCANCEL                  0x00000001
#define MB_ABORTRETRYIGNORE          0x00000002
#define MB_YESNOCANCEL               0x00000003
#define MB_YESNO                     0x00000004
#define MB_RETRYCANCEL               0x00000005
#ifdef _WIN32
#define MB_CANCELTRYCONTINUE         0x00000006
#endif
#define MB_ICONHAND                  0x00000010
#define MB_ICONSTOP                  0x00000010
#define MB_ICONERROR                 0x00000010
#define MB_ICONQUESTION              0x00000020
#define MB_ICONEXCLAMATION           0x00000030
#define MB_ICONWARNING               0x00000030
#define MB_ICONASTERISK              0x00000040
#define MB_ICONINFORMATION           0x00000040
#define MB_USERICON                  0x00000080
#define MB_DEFBUTTON1                0x00000000
#define MB_DEFBUTTON2                0x00000100
#define MB_DEFBUTTON3                0x00000200
#ifdef _WIN32
#define MB_DEFBUTTON4                0x00000300
#endif
#define MB_APPLMODAL                 0x00000000
#define MB_SYSTEMMODAL               0x00001000
#define MB_TASKMODAL                 0x00002000
#ifdef _WIN32
#define MB_HELP                      0x00004000
#endif
#define MB_NOFOCUS                   0x00008000 /* Q87341 says internal -- is it even in Win32? */
#ifdef _WIN32
#define MB_SETFOREGROUND             0x00010000
#define MB_DEFAULT_DESKTOP_ONLY      0x00020000
#define MB_SERVICE_NOTIFICATION_NT3X 0x00040000
#define MB_TOPMOST                   0x00040000
#define MB_RIGHT                     0x00080000
#define MB_RTLREADING                0x00100000
#define MB_SERVICE_NOTIFICATION      0x00200000
#endif

/* FIXME this is a generic list of common IDs, not specific to msgbox */
#define IDOK        1
#define IDCANCEL    2
#define IDABORT     3
#define IDRETRY     4
#define IDIGNORE    5
#define IDYES       6
#define IDNO        7
#ifdef _WIN32
#define IDTRYAGAIN 10
#define IDCONTINUE 11
#endif

#ifdef _WIN32

#define MessageBox _AW(MessageBox)

USERAPI int APIENTRY
MessageBoxW(struct HWND__        *hWnd,
            const char16_t       *lpText,
            const char16_t       *lpCaption,
            unsigned              uType);

#else
#define MessageBoxA MessageBox
#endif

USERAPI int APIENTRY
MessageBoxA(struct HWND__ __near *hWnd,
            const char     __far *lpText,
            const char     __far *lpCaption,
            unsigned              uType);

/* FIXME MessageBoxEx, MessageBoxIndirect */

#ifdef __cplusplus
}
#endif

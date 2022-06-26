/* requires windef.h */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef USERAPI
#define USERAPI DECLSPEC_IMPORT
#endif

struct ATOM__;
struct HBRUSH__;
struct HINSTANCE__;

typedef struct HCURSOR__ __near *HCURSOR;
typedef struct HICON__   __near *HICON;
typedef struct HMENU__   __near *HMENU;
typedef struct HWND__    __near *HWND;

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
MessageBoxW(HWND              hWnd,
            const char16_t   *lpText,
            const char16_t   *lpCaption,
            unsigned          uType);

#else
#define MessageBoxA MessageBox
#endif

USERAPI int APIENTRY
MessageBoxA(HWND              hWnd,
            const char __far *lpText,
            const char __far *lpCaption,
            unsigned          uType);

/* FIXME MessageBoxEx, MessageBoxIndirect */

/* WNDPROC, DefWindowProc */

typedef ULONG_PTR CALLBACK
(*WNDPROC)(HWND      hWnd,
           unsigned  uMsg,
           UINT_PTR  wParam,
           ULONG_PTR lParam);

#ifdef _WIN32

#define DefWindowProc _AW(DefWindowProc)

USERAPI ULONG_PTR APIENTRY
DefWindowProcW(HWND      hWnd,
               unsigned  uMsg,
               UINT_PTR  wParam,
               ULONG_PTR lParam);

#else
#define DefWindowProcA DefWindowProc
#endif

USERAPI ULONG_PTR APIENTRY
DefWindowProcA(HWND      hWnd,
               unsigned  uMsg,
               UINT_PTR  wParam,
               ULONG_PTR lParam);

/* RegisterClass */

#define CS_VREDRAW         0x0001
#define CS_HREDRAW         0x0002
#define CS_KEYCVTWINDOW    0x0004 /* pre-2.0 */
#define CS_DBLCLKS         0x0008
#define CS_OEMCHARS        0x0010 /* pre-3.0 */
#define CS_OWNDC           0x0020
#define CS_CLASSDC         0x0040
#define CS_MENUPOPUP       0x0080 /* undocumented -- obsolete or synonym */
#define CS_PARENTDC        0x0080
#define CS_NOKEYCVT        0x0100 /* undocumented -- pre-2.0 */
/* Win16 >= 2.0 */
#define CS_NOCLOSE         0x0200
/* unknown                 0x0400 */
#define CS_SAVEBITS        0x0800
#define CS_BYTEALIGNCLIENT 0x1000
#define CS_BYTEALIGNWINDOW 0x2000
/* Win16 >= 3.0 */
#define CS_GLOBALCLASS     0x4000 /* implicit pre-3.0 */
/* unknown                 0x8000 */
#ifdef _WIN32
/* Win32 >= 4.0 */
#define CS_IME             0x00010000 /* undocumented */
/* Win32 >= 5.1 */
#define CS_DROPSHADOW      0x00020000
#endif

#ifdef _WIN32

#define tagWNDCLASS _AW(tagWNDCLASS)
#define WNDCLASS    _AW(WNDCLASS)

typedef struct tagWNDCLASSW {
	unsigned                   style;
	WNDPROC                    lpfnWndProc;
	int                        cbClsExtra;
	int                        cbWndExtra;
	struct HINSTANCE__        *hInstance;
	HICON                      hIcon;
	HCURSOR                    hCursor;
	struct HBRUSH__           *hbrBackground;
	const char16_t            *lpszMenuName;
	const char16_t            *lpszClassName;
} WNDCLASSW;

#else
#define tagWNDCLASSA tagWNDCLASS
#define WNDCLASSA    WNDCLASS
#endif

typedef struct tagWNDCLASSA {
	unsigned                   style;
	WNDPROC                    lpfnWndProc;
	int                        cbClsExtra;
	int                        cbWndExtra;
	struct HINSTANCE__ __near *hInstance;
	HICON                      hIcon;
	HCURSOR                    hCursor;
	struct HBRUSH__    __near *hbrBackground;
	const char          __far *lpszMenuName;
	const char          __far *lpszClassName;
} WNDCLASSA;

#ifdef _WIN32

#define RegisterClass _AW(RegisterClass)

USERAPI struct ATOM__ *APIENTRY
RegisterClassW(const WNDCLASSW       *lpWndClass);

#else
#define RegisterClassA RegisterClass
#endif

#ifdef _WIN32 /* Win16 >= 3.1 as well, actually */
USERAPI struct ATOM__ *APIENTRY
#else
USERAPI int APIENTRY
#endif
RegisterClassA(const WNDCLASSA __far *lpWndClass);

/* FIXME WNDCLASSEX */

/* CreateWindow, CreateWindowEx */

/* CreateWindow: x, y, width, height */
#define CW_USEDEFAULT INT_MIN

/* CreateWindow: dwStyle */
#define WS_POPUP        0x80000000
#define WS_CHILD        0x40000000
#define WS_ICONIC       0x20000000 /* pre-2.0 name */
#define WS_MINIMIZE     0x20000000
#define WS_VISIBLE      0x10000000
#define WS_DISABLED     0x08000000
#define WS_CLIPSIBLINGS 0x04000000
#define WS_CLIPCHILDREN 0x02000000
#define WS_MAXIMIZE     0x01000000 /* Win16 >= 2.0 */
#define WS_CAPTION      0x00C00000
#define WS_BORDER       0x00800000
#define WS_DLGFRAME     0x00400000
#define WS_VSCROLL      0x00200000
#define WS_HSCROLL      0x00100000
#define WS_SYSMENU      0x00080000
#define WS_SIZEBOX      0x00040000 /* pre-2.0 name */
#define WS_THICKFRAME   0x00040000
#define WS_GROUP        0x00020000
#define WS_MINIMIZEBOX  0x00020000 /* Win16 >= 2.0 */
#define WS_TABSTOP      0x00010000
#define WS_MAXIMIZEBOX  0x00010000 /* Win16 >= 2.0 */
#define WS_TILED        0x00000000 /* pre-2.0 name */
#define WS_OVERLAPPED   0x00000000

#define WS_TILEDWINDOW      (WS_TILED       | \
                             WS_CAPTION     | \
                             WS_SYSMENU     | \
                             WS_THICKFRAME  | \
                             /* Win16 >= 2.0 */ \
                             WS_MINIMIZEBOX | \
                             WS_MAXIMIZEBOX) /* pre-2.0 name */
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED  | \
                             WS_CAPTION     | \
                             WS_SYSMENU     | \
                             WS_THICKFRAME  | \
                             WS_MINIMIZEBOX | \
                             WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW      (WS_POPUP | WS_BORDER | WS_SYSMENU)
#define WS_CHILDWINDOW       WS_CHILD

/* FIXME WS_EX_* */

#ifdef _WIN32

#define CreateWindowEx _AW(CreateWindowEx)

USERAPI HWND APIENTRY
CreateWindowExW(uint32_t                   dwExStyle,
                const char16_t            *lpClassName,
                const char16_t            *lpWindowName,
                uint32_t                   dwStyle,
                int                        X,
                int                        Y,
                int                        nWidth,
                int                        nHeight,
                HWND                       hWndParent,
                HMENU                      hMenu,
                struct HINSTANCE__        *hInstance,
                const void                *lpParam);

#else
#define CreateWindowExA CreateWindowEx
#endif

USERAPI HWND APIENTRY /* Win16 >= 3.0 */
CreateWindowExA(uint32_t                   dwExStyle,
                const char          __far *lpClassName,
                const char          __far *lpWindowName,
                uint32_t                   dwStyle,
                int                        X,
                int                        Y,
                int                        nWidth,
                int                        nHeight,
                HWND                       hWndParent,
                HMENU                      hMenu,
                struct HINSTANCE__ __near *hInstance,
                const void          __far *lpParam);

#ifdef _WIN32

#define CreateWindow _AW(CreateWindow)

#define CreateWindowW(CN, WN, S, X, Y, W, H, HP, HM, HI, P) \
	CreateWindowExW(0, CN, WN, S, X, Y, W, H, HP, HM, HI, P)

#define CreateWindowA(CN, WN, S, X, Y, W, H, HP, HM, HI, P) \
	CreateWindowExA(0, CN, WN, S, X, Y, W, H, HP, HM, HI, P)

#else

#define CreateWindowA CreateWindow

USERAPI HWND APIENTRY
CreateWindowA(const char          __far *lpClassName,
              const char          __far *lpWindowName,
              uint32_t                   dwStyle,
              int                        X,
              int                        Y,
              int                        nWidth,
              int                        nHeight,
              HWND                       hWndParent,
              HMENU                      hMenu,
              struct HINSTANCE__ __near *hInstance,
              const void          __far *lpParam);

#endif

/* ShowWindow */

#define HIDE_WINDOW          0 /* pre-2.0 name */
#define SW_HIDE              0
#define SHOW_OPENWINDOW      1 /* pre-2.0 name */
#define SW_SHOWNORMAL        1 /* pre-Win32 name */
#define SW_NORMAL            1
#define SHOW_ICONWINDOW      2 /* pre-2.0 name */
#define SW_SHOWMINIMIZED     2
#define SHOW_FULLSCREEN      3 /* pre-2.0 name */
#define SW_SHOWMAXIMIZED     3 /* pre-Win32 name */
#define SW_MAXIMIZE          3
#define SHOW_OPENNOACTIVATE  4 /* pre-2.0 name */
#define SW_SHOWNOACTIVATE    4
/* Win16 >= 2.0 */
#define SW_SHOW              5
#define SW_MINIMIZE          6
#define SW_SHOWMINNOACTIVATE 7
#define SW_SHOWNA            8
#define SW_RESTORE           9
#ifdef _WIN32
#define SW_SHOWDEFAULT      10
/* Win32 >= 5.0 */
#define SW_FORCEMINIMIZE    11
#endif

USERAPI int APIENTRY ShowWindow(HWND hWnd, int nCmdShow);

/* UpdateWindow */

USERAPI int APIENTRY UpdateWindow(HWND hWnd);

/* GetMessage, TranslateMessage, DispatchMessage, PostQuitMessage */

typedef struct tagMSG {
	HWND      hwnd;
	unsigned  message;
	UINT_PTR  wParam;
	ULONG_PTR lParam;
	uint32_t  time;
	POINT     pt;
} MSG;

#ifdef _WIN32

#define GetMessage _AW(GetMessage)

USERAPI int APIENTRY
GetMessageW(MSG       *lpMsg,
            HWND       hWnd,
            unsigned   uMsgFilterMin,
            unsigned   uMsgFilterMax);

#else
#define GetMessageA GetMessage
#endif

USERAPI int APIENTRY
GetMessageA(MSG __far *lpMsg,
            HWND       hWnd,
            unsigned   uMsgFilterMin,
            unsigned   uMsgFilterMax);

USERAPI int APIENTRY TranslateMessage(MSG __far *lpMsg);

#ifdef _WIN32
#define DispatchMessage _AW(DispatchMessage)
USERAPI ULONG_PTR APIENTRY DispatchMessageW(const MSG       *lpMsg);
#else
#define DispatchMessageA DispatchMessage
#endif

USERAPI ULONG_PTR APIENTRY DispatchMessageA(const MSG __far *lpMsg);

USERAPI void APIENTRY PostQuitMessage(int nExitCode);

#ifdef __cplusplus
}
#endif

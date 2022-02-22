/* requires windef.h */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
int PASCAL
wWinMain(struct HINSTANCE__        *hInstance,
         struct HINSTANCE__        *hPrevInstance,
         char16_t                  *lpCmdLine,
         int                        nCmdShow);
#endif

int PASCAL
WinMain (struct HINSTANCE__ __near *hInstance,
         struct HINSTANCE__ __near *hPrevInstance,
         char __far                *lpCmdLine,
         int                        nCmdShow);

#ifdef UNICODE
#define _tWinMain wWinMain
#else
#define _tWinMain  WinMain
#endif

#ifdef __cplusplus
}
#endif

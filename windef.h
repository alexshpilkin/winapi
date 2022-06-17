#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#if defined _WIN32 && !defined _UTF16

#if __STDC_VERSION__ >= 200904L /* N1362 */ || __cplusplus >= 200705L /* N2284 */
#include <uchar.h>
#define _UTF16(S) u##S
#else
#include <wchar.h>
typedef wchar_t char16_t;
#define _UTF16(S) L##S
#if WCHAR_MAX <= 65535 && (WCHAR_MIN >= 0 || WCHAR_MIN >= -32768)
/* __STDC_ISO_10646__ can't be defined, so we can only hope */
#define __STDC_UTF_16__ 1
#endif
#endif

#ifndef __STDC_UTF_16__
#error "no usable char16_t, define _UTF16 to override"
#endif

#endif

#ifndef DECLSPEC_IMPORT
#ifdef _WIN32
#define DECLSPEC_IMPORT __declspec(dllimport)
#else
#define DECLSPEC_IMPORT extern
#endif
#endif

#ifdef _WIN32
#define __far  /* for pointers and DDE handles */
#define __near /* for handles */
#ifndef APIENTRY
#define APIENTRY __stdcall
#endif
#ifndef CALLBACK
#define CALLBACK __stdcall
#endif
#ifndef PASCAL /* for WinMain() -- yes, it's not actually the Pascal one */
#define PASCAL __stdcall
#endif
#else
#ifndef APIENTRY
#define APIENTRY __far __pascal
#endif
#ifndef CALLBACK
#define CALLBACK __export __far __pascal
#endif
#ifndef PASCAL
#define PASCAL /* FIXME __near? */ __pascal
#endif
#endif

#if __STDC_VERSION__ >= 199711L /* N794 */
#define ANYSIZE_ARRAY
#elif defined __GNUC__ /* FIXME and others? C++? */
#define ANYSIZE_ARRAY 0
#else
#define ANYSIZE_ARRAY 1
#endif

#if __STDC_VERSION__ >= 201811L /* N2310 */
#define _STATIC_ASSERT(E) _Static_assert((E))
#elif __cplusplus >= 201411L /* N4296 */
#define _STATIC_ASSERT(E) static_assert((E))
#elif __STDC_VERSION__ >= 200904L /* N1362 */
#define _STATIC_ASSERT(E) _Static_assert((E), #E)
#elif __cplusplus >= 200504L /* N1804 */
#define _STATIC_ASSERT(E) static_assert((E), #E)
#else
#define _STATIC_ASSERT(E) extern int _ASSERTION_FAILED[2*!!(E)-1]
#endif

#ifdef UNICODE
#ifndef _WIN32
#error "UNICODE requires _WIN32"
#endif
typedef char16_t TCHAR;
#define _T(S)  u##S
#define _AW(N) N##W
#else
typedef char TCHAR;
#define _T(S)  S
#define _AW(N) N##A
#endif

#ifdef __cplusplus
}
#endif

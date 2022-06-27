#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>
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
#if WCHAR_MAX - WCHAR_MIN == 65535
/* __STDC_ISO_10646__ can't be defined, so we can only hope */
#define __STDC_UTF_16__ 1
#endif
#endif

#ifndef __STDC_UTF_16__
#error "no usable char16_t, define _UTF16 to override"
#endif

#endif

#ifndef _HAS_STD_ATTRIBUTE
#if __STDC_VERSION__ >= 201906L /* N2385 */ && defined __has_c_attribute
#define _HAS_STD_ATTRIBUTE(A) __has_c_attribute(__ ## A ## __)
#elif __cplusplus >= 200810L /* N2798 */ && defined __has_cpp_attribute
#define _HAS_STD_ATTRIBUTE(A) __has_cpp_attribute(__ ## A ## __)
#else
#define _HAS_STD_ATTRIBUTE(A) _HAS_STD_ATTRIBUTE_ ## A
#define _HAS_STD_ATTRIBUTE_noreturn (__STDC_VERSION__ >= 202206L /* N2912 */ || __cplusplus >= 200810L /* N2798 */)
#endif
#endif

#ifndef _HAS_GNU_ATTRIBUTE
#ifdef __has_attribute
#define _HAS_GNU_ATTRIBUTE(A) __has_attribute(__ ## A ## __)
#else
#define _HAS_GNU_ATTRIBUTE(A) _HAS_GNU_ATTRIBUTE_ ## A
#define _HAS_GNU_ATTRIBUTE_noreturn (__GNUC__ + (__GNUC_MINOR__ >= 5) > 2)
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

#ifndef ANYSIZE_ARRAY
#if __STDC_VERSION__ >= 199711L /* N794 */
#define ANYSIZE_ARRAY
#elif defined __GNUC__ /* FIXME and others? C++? */
#define ANYSIZE_ARRAY 0
#else
#define ANYSIZE_ARRAY 1
#endif
#endif

#ifndef DUMMYUNIONNAME
#if !defined NONAMELESSUNION && \
    (__STDC_VERSION__ >= 200911L /* N1425 */ || \
     defined __cplusplus /* C++98 and later */ || \
     __GNUC__ + (__GNUC_MINOR__ >= 1) > 3 || \
     defined __WATCOMC__ /* FIXME version? */) /* FIXME MSVC */
#define DUMMYUNIONNAME
#else
#define DUMMYUNIONNAME u
#endif
#endif

#ifndef _STATIC_ASSERT
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
#endif

#ifndef _NORETURN
#if _HAS_STD_ATTRIBUTE(noreturn)
#define _NORETURN [[__noreturn__]]
#elif __STDC_VERSION__ >= 201006L /* N1494 */
#define _NORETURN _Noreturn
#elif _HAS_GNU_ATTRIBUTE(noreturn)
#define _NORETURN __attribute__((__noreturn__))
#else /* FIXME __declspec(noreturn) */
#define _NORETURN
#endif
#endif

#ifdef UNICODE
#ifndef _WIN32
#error "UNICODE requires _WIN32"
#endif
typedef char16_t TCHAR;
#define _T(S)  _UTF16(S)
#define _AW(N) N##W
#else
typedef char TCHAR;
#define _T(S)  S
#define _AW(N) N##A
#endif

#ifdef _WIN32
typedef uintptr_t UINT_PTR, ULONG_PTR;
#else
/* either of these might be the compiler's uintptr_t */
typedef uint16_t UINT_PTR;
typedef uint32_t ULONG_PTR;
#endif

typedef struct tagPOINT {
	int x, y;
} POINT;

typedef struct tagRECT {
	int left, top, right, bottom;
} RECT;

#define INVALID_HANDLE_VALUE ((void *)-1)
/* #define HFILE_ERROR (-1) -- not a HFILE */

#ifdef __cplusplus
}
#endif

/* requires windef.h */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef KERNELAPI
#define KERNELAPI DECLSPEC_IMPORT
#endif

typedef struct HFILE__        __near *HFILE; /* deliberate incompatibility */
typedef struct HINSTANCE__    __near *HINSTANCE;
typedef struct HTRANSACTION__ __near *HTRANSACTION;

struct _SECURITY_ATTRIBUTES; /* FIXME */

#define MAX_PATH 260

/* FIXME there are much more, and this is not KERNEL-specific */
#define GENERIC_READ    0x80000000
#define GENERIC_WRITE   0x40000000
#define GENERIC_EXECUTE 0x20000000
#define GENERIC_ALL     0x10000000

/* ExitProcess */

#ifdef _WIN32

KERNELAPI void _NORETURN APIENTRY ExitProcess(unsigned uExitCode);

#else

#ifdef __WATCOMC__ /* FIXME version? */
void _NORETURN __dosexit(unsigned char, unsigned char);
#pragma aux __dosexit parm [ah] [al] = 0xCD 0x21 /* int 21h */
#define ExitProcess(U) (__dosexit(0x4C, (1 ? (U) : 0u) & 0xFF))
#endif

#endif

/* GetLastError, SetLastError */

#ifdef _WIN32

KERNELAPI uint32_t APIENTRY GetLastError(void);
KERNELAPI void     APIENTRY SetLastError(uint32_t dwErrCode);

#endif

/* OpenFile */

#define OFS_MAXPATHNAME 128

typedef struct _OFSTRUCT {
	unsigned char cBytes;
	unsigned char fFixedDisk;
	uint16_t      nErrCode;
	uint16_t      Reserved1,
	              Reserved2;
	char          szPathName[OFS_MAXPATHNAME];
} OFSTRUCT;

#define OF_READ             0x0000
#define OF_WRITE            0x0001
#define OF_READWRITE        0x0002
#define OF_SHARE_COMPAT     0x0000
#define OF_SHARE_EXCLUSIVE  0x0010
#define OF_SHARE_DENY_WRITE 0x0020
#define OF_SHARE_DENY_READ  0x0030
#define OF_SHARE_DENY_NONE  0x0040
#define OF_PARSE            0x0100
#define OF_DELETE           0x0200
#define OF_VERIFY           0x0400
#define OF_SEARCH           0x0400
#define OF_CANCEL           0x0800
#define OF_CREATE           0x1000
#define OF_PROMPT           0x2000
#define OF_EXIST            0x4000
#define OF_REOPEN           0x8000

KERNELAPI int APIENTRY
OpenFile(const char __far *lpFileName,
         OFSTRUCT   __far *lpReOpenBuff, /* FIXME const? */
         unsigned          uStyle);

/* CreateFile, CreateFileTransacted, CreateFile2 */

#ifdef _WIN32

/* CreateFile: dwShareMode */
#define FILE_SHARE_NONE   0
#define FILE_SHARE_READ   1
#define FILE_SHARE_WRITE  2
#define FILE_SHARE_DELETE 4

/* CreateFile: dwCreationDisposition */
#define CREATE_NEW        1
#define CREATE_ALWAYS     2
#define OPEN_EXISTING     3
#define OPEN_ALWAYS       4
#define TRUNCATE_EXISTING 5

/* CreateFile: dwFlagsAndAttributes */
/* FIXME these are generic, and CreateFile accepts only a subset */
#define FILE_ATTRIBUTE_READONLY              0x00000001
#define FILE_ATTRIBUTE_HIDDEN                0x00000002
#define FILE_ATTRIBUTE_SYSTEM                0x00000004
#define FILE_ATTRIBUTE_LABEL                 0x00000008
#define FILE_ATTRIBUTE_VOLUME                0x00000008
#define FILE_ATTRIBUTE_VOLUME_LABEL          0x00000008
#define FILE_ATTRIBUTE_DIRECTORY             0x00000010
#define FILE_ATTRIBUTE_SUBDIRECTORY          0x00000010
#define FILE_ATTRIBUTE_ARCHIVE               0x00000020
#define FILE_ATTRIBUTE_DEVICE                0x00000040
/*      FILE_ATTRIBUTE_ENCRYPTED             0x00000040 ??? */
#define FILE_ATTRIBUTE_NORMAL                0x00000080
#define FILE_ATTRIBUTE_TEMPORARY             0x00000100
#define FILE_ATTRIBUTE_ATOMIC_WRITE          0x00000200
#define FILE_ATTRIBUTE_SPARSE_FILE           0x00000200
#define FILE_ATTRIBUTE_XACTION_WRITE         0x00000400
#define FILE_ATTRIBUTE_REPARSE_POINT         0x00000400
#define FILE_ATTRIBUTE_COMPRESSED            0x00000800
#define FILE_ATTRIBUTE_OFFLINE               0x00001000
#define FILE_ATTRIBUTE_PROPERTY_SET          0x00002000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED   0x00002000
#define FILE_ATTRIBUTE_ENCRYPTED             0x00004000
#define FILE_ATTRIBUTE_INTEGRITY_STREAM      0x00008000
#define FILE_ATTRIBUTE_VIRTUAL               0x00010000
#define FILE_ATTRIBUTE_NO_SCRUB_DATA         0x00020000
#define FILE_ATTRIBUTE_EA                    0x00040000
#define FILE_ATTRIBUTE_RECALL_ON_OPEN        0x00040000
#define FILE_ATTRIBUTE_PINNED                0x00080000
#define FILE_ATTRIBUTE_UNPINNED              0x00100000
/* undocumented                              0x00200000 ??? */
#define FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS 0x00400000

#define FILE_FLAG_OPEN_NO_RECALL             0x00100000
#define FILE_FLAG_OPEN_REPARSE_POINT         0x00200000
#define FILE_FLAG_SESSION_AWARE              0x00800000
#define FILE_FLAG_POSIX_SEMANTICS            0x01000000
#define FILE_FLAG_BACKUP_SEMANTICS           0x02000000
#define FILE_FLAG_DELETE_ON_CLOSE            0x04000000
#define FILE_FLAG_SEQUENTIAL_SCAN            0x08000000
#define FILE_FLAG_RANDOM_ACCESS              0x10000000
#define FILE_FLAG_NO_BUFFERING               0x20000000
#define FILE_FLAG_OVERLAPPED                 0x40000000
#define FILE_FLAG_WRITE_THROUGH              0x80000000

#define SECURITY_SQOS_PRESENT                0x00100000
/* #define SECURITY_ANONYMOUS (SecurityAnonymous << 16) etc. from NT */

typedef struct _CREATEFILE2_EXTENDED_PARAMETERS {
	uint32_t                     dwSize;
	uint32_t                     dwFileAttributes;
	uint32_t                     dwFileFlags;
	uint32_t                     dwSecurityQosFlags;
	struct _SECURITY_ATTRIBUTES *lpSecurityAttributes;
	HFILE                        hTemplateFile;
} CREATEFILE2_EXTENDED_PARAMETERS;

#define CreateFile _AW(CreateFile)

KERNELAPI HFILE APIENTRY
CreateFileW(const char16_t              *lpFileName,
            uint32_t                     dwDesiredAccess,
            uint32_t                     dwShareMode,
            struct _SECURITY_ATTRIBUTES *lpSecurityAttributes, /* FIXME const? */
            uint32_t                     dwCreationDisposition,
            uint32_t                     dwFlagsAndAttributes,
            HFILE                        hTemplateFile);

KERNELAPI HFILE APIENTRY
CreateFileA(const char                  *lpFileName,
            uint32_t                     dwDesiredAccess,
            uint32_t                     dwShareMode,
            struct _SECURITY_ATTRIBUTES *lpSecurityAttributes,
            uint32_t                     dwCreationDisposition,
            uint32_t                     dwFlagsAndAttributes,
            HFILE                        hTemplateFile);

#define CreateFileTransacted _AW(CreateFileTransacted)

KERNELAPI HFILE APIENTRY
CreateFileTransactedW(const char                  *lpFileName,
                      uint32_t                     dwDesiredAccess,
                      uint32_t                     dwShareMode,
                      struct _SECURITY_ATTRIBUTES *lpSecurityAttributes,
                      uint32_t                     dwCreationDisposition,
                      uint32_t                     dwFlagsAndAttributes,
                      HFILE                        hTemplateFile,
                      struct HTRANSACTION__       *hTransaction,
                      const uint16_t              *pusMinVersion,
                      void                        *lpExtendedParameter);

KERNELAPI HFILE APIENTRY
CreateFileTransactedA(const char16_t              *lpFileName,
                      uint32_t                     dwDesiredAccess,
                      uint32_t                     dwShareMode,
                      struct _SECURITY_ATTRIBUTES *lpSecurityAttributes,
                      uint32_t                     dwCreationDisposition,
                      uint32_t                     dwFlagsAndAttributes,
                      HFILE                        hTemplateFile,
                      struct HTRANSACTION__       *hTransaction,
                      const uint16_t              *pusMinVersion,
                      void                        *lpExtendedParameter);

KERNELAPI HFILE APIENTRY 
CreateFile2(const char16_t                        *lpFileName,
            uint32_t                               dwDesiredAccess,
            uint32_t                               dwShareMode,
            uint32_t                               dwCreationDisposition,
            const CREATEFILE2_EXTENDED_PARAMETERS *pCreateExParams);

#endif

#ifdef __cplusplus
}
#endif

/* requires windef.h */

#define IMAGE_DOS_SIGNATURE 0x5A4D /* MZ */

typedef struct _IMAGE_DOS_HEADER {
	uint16_t e_magic;
	uint16_t e_cblp;
	uint16_t e_cp;
	uint16_t e_crlc;
	uint16_t e_cparhdr;
	uint16_t e_minalloc, e_maxalloc;
	uint16_t e_ss, e_sp;
	uint16_t e_csum;
	uint16_t e_ip, e_cs;
	uint16_t e_lfarlc;
	uint16_t e_ovno;
	uint16_t e_res[4];
	uint16_t e_oemid, e_oeminfo;
	uint16_t e_res2[10];
	int32_t  e_lfanew;
} IMAGE_DOS_HEADER;

_STATIC_ASSERT(sizeof(IMAGE_DOS_HEADER) == 64);

#define IMAGE_FILE_MACHINE_I386 0x014C

typedef struct _IMAGE_FILE_HEADER {
	uint16_t Machine;
	uint16_t NumberOfSections;
	uint32_t TimeDateStamp;
	uint32_t PointerToSymbolTable;
	uint32_t NumberOfSymbols;
	uint16_t SizeOfOptionalHeader;
	uint16_t Characteristics;
} IMAGE_FILE_HEADER;

_STATIC_ASSERT(sizeof(IMAGE_FILE_HEADER) == 20);

typedef struct _IMAGE_DATA_DIRECTORY {
	uint32_t VirtualAddress, Size;
} IMAGE_DATA_DIRECTORY;

_STATIC_ASSERT(sizeof(IMAGE_DATA_DIRECTORY) == 8);

#define IMAGE_NT_OPTIONAL_HDR_MAGIC 0x010B /* aka ZMAGIC */

typedef struct _IMAGE_OPTIONAL_HEADER {
	/* COFF standard */
	uint16_t Magic;
	uint8_t  MajorLinkerVersion, MinorLinkerVersion;
	uint32_t SizeOfCode, SizeOfInitializedData, SizeOfUninitializedData;
	uint32_t AddressOfEntryPoint;
	uint32_t BaseOfCode, BaseOfData;

	/* PE-specific */
	uint32_t ImageBase;
	uint32_t SectionAlignment, FileAlignment;
	uint16_t MajorOperatingSystemVersion, MinorOperatingSystemVersion,
	         MajorImageVersion, MinorImageVersion,
	         MajorSubsystemVersion, MinorSubsystemVersion;
	uint32_t Win32VersionValue;
	uint32_t SizeOfImage, SizeOfHeaders;
	uint32_t CheckSum;
	uint16_t Subsystem;
	uint16_t DllCharacteristics;
	uint32_t SizeOfStackReserve, SizeOfStackCommit,
	         SizeOfHeapReserve, SizeOfHeapCommit;
	uint32_t LoaderFlags;
	uint32_t NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[];
} IMAGE_OPTIONAL_HEADER;

_STATIC_ASSERT(sizeof(IMAGE_OPTIONAL_HEADER) == 96);

#define IMAGE_NT_SIGNATURE 0x00004550 /* PE\0\0 */

typedef struct _IMAGE_NT_HEADERS {
	uint32_t Signature;
	IMAGE_FILE_HEADER FileHeader;
	IMAGE_OPTIONAL_HEADER OptionalHeader;
} IMAGE_NT_HEADERS;

_STATIC_ASSERT(sizeof(IMAGE_NT_HEADERS) == 120);

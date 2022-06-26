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

typedef struct _IMAGE_FILE_HEADER /* filehdr */ {
	uint16_t Machine;              /* f_magic  */
	uint16_t NumberOfSections;     /* f_nscns  */
	uint32_t TimeDateStamp;        /* f_timdat */
	uint32_t PointerToSymbolTable; /* f_symptr */
	uint32_t NumberOfSymbols;      /* f_nsyms  */
	uint16_t SizeOfOptionalHeader; /* f_opthdr */
	uint16_t Characteristics;      /* f_flags  */
} IMAGE_FILE_HEADER;

_STATIC_ASSERT(sizeof(IMAGE_FILE_HEADER) == 20);

typedef struct _IMAGE_DATA_DIRECTORY {
	uint32_t VirtualAddress, Size;
} IMAGE_DATA_DIRECTORY;

_STATIC_ASSERT(sizeof(IMAGE_DATA_DIRECTORY) == 8);

#define IMAGE_NT_OPTIONAL_HDR_MAGIC 0x010B /* ZMAGIC  */

typedef struct _IMAGE_OPTIONAL_HEADER /* aouthdr */ {
	/* COFF standard */
	uint16_t Magic;                    /* magic   */
	uint8_t  MajorLinkerVersion,
	         MinorLinkerVersion;       /* vstamp  */
	uint32_t SizeOfCode,               /* tsize   */
	         SizeOfInitializedData,    /* dsize   */
	         SizeOfUninitializedData;  /* bsize   */
	uint32_t AddressOfEntryPoint;      /* entry   */
	uint32_t BaseOfCode,               /* text_start */
	         BaseOfData;               /* data_start */

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

#define IMAGE_SIZEOF_SHORT_NAME 8

typedef struct _IMAGE_SECTION_HEADER /* scnhdr */ {
	char Name[IMAGE_SIZEOF_SHORT_NAME]; /* s_name    */
	union {
		uint32_t PhysicalAddress;
		uint32_t VirtualSize;
	} DUMMYUNIONNAME;                   /* s_paddr   */
	uint32_t VirtualAddress;            /* s_vaddr   */
	uint32_t SizeOfRawData;             /* s_size    */
	uint32_t PointerToRawData,          /* s_scnptr  */
	         PointerToRelocations,      /* s_relptr  */
	         PointerToLinenumbers;      /* s_lnnoptr */
	uint16_t NumberOfRelocations,       /* s_nreloc  */
	         NumberOfLinenumbers;       /* s_nlnno   */
	uint32_t Characteristics;           /* s_flags   */
} IMAGE_SECTION_HEADER;

_STATIC_ASSERT(sizeof(IMAGE_SECTION_HEADER) == 40);

#ifndef _LIBTF2MOD_COMMON_H
#define _LIBTF2MOD_COMMON_H


typedef struct {
	const char *name;
	const char *path;
	
	/* generic file stuff */
	int         fd;
	struct stat stat;
	size_t      size;
	void       *map;
	
	/* libdl stuff */
	void            *handle;
	struct link_map *linkmap;
	uintptr_t        baseaddr;
	
	/* elf symtab stuff */
	Elf        *elf;
	Elf32_Ehdr *elf_hdr;
	Elf_Data   *symtab_data;
	GElf_Shdr   symtab_shdr;
	int         symtab_count;
} library_info_t;


typedef struct {
	library_info_t *lib;
	uintptr_t       addr;
	uintptr_t       size;
	const char     *name;
} symbol_t;

typedef struct {
	const char *name;
	const char *name_demangled;
	
	uintptr_t func_addr;
	size_t    func_size;
	
	bool      has_detour;
	uintptr_t detour_addr;
	
	uintptr_t trampoline_addr;
	size_t    trampoline_size;
	uintptr_t trampoline_dest;
	
	size_t  restore_len;
	uint8_t restore_buf[20];
} func_t;


#define CONV_LE(_dword) \
	(uint8_t)((uint32_t)(_dword) >>  0), \
	(uint8_t)((uint32_t)(_dword) >>  8), \
	(uint8_t)((uint32_t)(_dword) >> 16), \
	(uint8_t)((uint32_t)(_dword) >> 24),


#define pr_debug(_fmt, ...) \
	fprintf(stderr, "\e[37m" _fmt "\e[0m", ##__VA_ARGS__); fflush(stderr)
#define pr_info(_fmt, ...) \
	fprintf(stderr, "\e[97m" _fmt "\e[0m", ##__VA_ARGS__); fflush(stderr)
#define pr_warn(_fmt, ...) \
	fprintf(stderr, "\e[93m" _fmt "\e[0m", ##__VA_ARGS__); fflush(stderr)
#define pr_err(_fmt, ...) \
	fprintf(stderr, "\e[91m" _fmt "\e[0m", ##__VA_ARGS__); fflush(stderr)
#define pr_special(_fmt, ...) \
	fprintf(stderr, "\e[96m" _fmt "\e[0m", ##__VA_ARGS__); fflush(stderr)

#define warn(_fmt, ...) \
	warn("\e[93m" _fmt "\e[0m", ##__VA_ARGS__)
#define warnx(_fmt, ...) \
	warnx("\e[93m" _fmt "\e[0m", ##__VA_ARGS__)
#define err(_code, _fmt, ...) \
	err(_code, "\e[91m" _fmt "\e[0m", ##__VA_ARGS__)
#define errx(_code, _fmt, ...) \
	errx(_code, "\e[91m" _fmt "\e[0m", ##__VA_ARGS__)


#endif

#ifndef _LIBTF2MOD_COMMON_H
#define _LIBTF2MOD_COMMON_H


typedef struct {
	uintptr_t   addr;
	uintptr_t   size;
	const char *name;
} symbol_t;

typedef struct {
	char *name;
	char *name_demangled;
	
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


#define pr_debug(_fmt, ...) \
	fprintf(stderr, "\e[37m" _fmt "\e[0m", ##__VA_ARGS__)
#define pr_info(_fmt, ...) \
	fprintf(stderr, "\e[97m" _fmt "\e[0m", ##__VA_ARGS__)
#define pr_warn(_fmt, ...) \
	fprintf(stderr, "\e[93m" _fmt "\e[0m", ##__VA_ARGS__)
#define pr_err(_fmt, ...) \
	fprintf(stderr, "\e[91m" _fmt "\e[0m", ##__VA_ARGS__)
#define pr_special(_fmt, ...) \
	fprintf(stderr, "\e[96m" _fmt "\e[0m", ##__VA_ARGS__)

#define warn(_fmt, ...) \
	warn("\e[93m" _fmt "\e[0m", ##__VA_ARGS__)
#define warnx(_fmt, ...) \
	warnx("\e[93m" _fmt "\e[0m", ##__VA_ARGS__)
#define err(_code, _fmt, ...) \
	err(_code, "\e[91m" _fmt "\e[0m", ##__VA_ARGS__)
#define errx(_code, _fmt, ...) \
	errx(_code, "\e[91m" _fmt "\e[0m", ##__VA_ARGS__)


#endif

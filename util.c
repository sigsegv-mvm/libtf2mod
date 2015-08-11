#include "all.h"


uintptr_t calc_relative_jump(void *src, size_t off, void *dst)
{
	return ((uintptr_t)dst - (((uintptr_t)src + off) + 5));
}


void mem_unprotect(const void *addr, size_t len)
{
	void  *page_addr = (void *)((uintptr_t)addr & ~(PAGE_SIZE - 1));
	size_t page_len  = len + ((uintptr_t)addr % PAGE_SIZE);
	
	if (mprotect(page_addr, page_len,
		PROT_READ | PROT_WRITE | PROT_EXEC) != 0) {
		warn("mprotect failed in mem_unprotect(%p)", addr);
	}
}

void mem_protect(const void *addr, size_t len)
{
	void  *page_addr = (void *)((uintptr_t)addr & ~(PAGE_SIZE - 1));
	size_t page_len  = len + ((uintptr_t)addr % PAGE_SIZE);
	
	if (mprotect(page_addr, page_len,
		PROT_READ | PROT_EXEC) != 0) {
		warn("mprotect failed in mem_protect(%p)", addr);
	}
}


void func_unprotect(const func_t *func)
{
	mem_unprotect((void *)func->func_addr, func->func_size);
}

void func_protect(const func_t *func)
{
	mem_protect((void *)func->func_addr, func->func_size);
}


void mem_dump(const void *addr, size_t len, bool align)
{
	uintptr_t start = (uintptr_t)addr;
	uintptr_t end   = (uintptr_t)addr + len;
	
	if (align) {
		/* round down to 16 bytes */
		start &= ~0xf;
		
		/* round up to 16 bytes */
		if ((end & 0xf) != 0) {
			end &= ~0xf;
			end += 0x10;
		}
	}
	
	pr_info("mem_dump @ %p, len %u\n", addr, len);
	
	const uint8_t *ptr = (const uint8_t *)start;
	int i = 0;
	
	while (ptr != (uint8_t *)end) {
		if (i == 0) {
			pr_debug("  %08x: ", (uintptr_t)ptr);
		} else if (i == 8) {
			pr_debug(" ");
		}
		
		pr_debug(" %02x", *ptr);
		
		if (i == 15 || (ptr + 1) == (uint8_t *)end) {
			pr_debug("\n");
		}
		
		++ptr;
		if (++i >= 0x10) {
			i = 0;
		}
	}
}


void func_dump(const func_t *func)
{
	mem_dump((void *)func->func_addr, func->func_size, false);
}


uintptr_t find_string(const char *lib_name, const char *str, bool absolute)
{
	library_info_t *lib = lib_find(lib_name);
	
	size_t bin_len = lib->size;
	size_t str_len = strlen(str) + 1;
	
	const char *haystack = lib->map;
	
	for (int i = 0; i + str_len <= bin_len; ++i) {
		if (memcmp(haystack + i, str, str_len) == 0) {
			if (absolute) {
				return lib->baseaddr + i;
			} else {
				return i;
			}
		}
	}
	
	return 0;
}

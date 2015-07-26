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


uintptr_t find_string(const char *str)
{
	size_t bin_len = dl_size;
	size_t str_len = strlen(str) + 1;
	
	const char *haystack = dl_map;
	
	for (int i = 0; i + str_len <= bin_len; ++i) {
		if (memcmp(haystack + i, str, str_len) == 0) {
			return i;
		}
	}
	
	return 0;
}


uintptr_t datamap_findoffset(datamap_t *map, const char *name)
{
	//pr_debug("%s: name '%s' map %08x\n", __func__, name, map);
	while (map != NULL) {
		//mem_dump(map->dataDesc, sizeof(typedescription_t) * map->dataNumFields, false);
		//pr_debug("%s:  map->dataNumFields %d\n", __func__, map->dataNumFields);
		for (int i = 0; i < map->dataNumFields; ++i) {
			//pr_debug("%s:   i %d\n", __func__, i);
			//pr_debug("%s:   map->dataDesc[i].fieldName %08x\n", __func__, map->dataDesc[i].fieldName);
			if (map->dataDesc[i].fieldName == NULL) {
				continue;
			}
			//pr_debug("%s:   map->dataDesc[i].fieldName '%s'\n", __func__, map->dataDesc[i].fieldName);
			if (strcmp(name, map->dataDesc[i].fieldName) == 0) {
				return map->dataDesc[i].fieldOffset[TD_OFFSET_NORMAL];
			}
			//pr_debug("%s:   map->dataDesc[i].td %08x\n", __func__, map->dataDesc[i].td);
			if (map->dataDesc[i].td != NULL) {
				uintptr_t offset;
				if ((offset = datamap_findoffset(map->dataDesc[i].td,
					name)) != 0) {
					//pr_debug("%s:    return %04x\n", __func__, offset);
					return offset;
				}
				//pr_debug("%s:    nope\n", __func__);
			}
		}
		
		//pr_debug("%s: basemap %08x\n", __func__, map->baseMap);
		map = map->baseMap;
	}
	
	//pr_debug("%s: return 0\n", __func__);
	return 0;
}

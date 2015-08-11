#ifndef _LIBTF2MOD_UTIL_H
#define _LIBTF2MOD_UTIL_H


uintptr_t calc_relative_jump(void *src, size_t off, void *dst);

void mem_unprotect(const void *addr, size_t len);
void mem_protect(const void *addr, size_t len);

void func_unprotect(const func_t *func);
void func_protect(const func_t *func);

void mem_dump(const void *addr, size_t len, bool align);

void func_dump(const func_t *func);

uintptr_t find_string(const char *lib_name, const char *str, bool absolute);


extern void *__dynamic_cast(const void *__src_ptr,
	const void *__src_type,
	const void *__dst_type,
	ptrdiff_t __src2dst);

#define DYNAMIC_CAST(_src, _src_type, _dst_type) \
	__dynamic_cast(_src, typeinfo_for_ ## _src_type, typeinfo_for_ ## _dst_type, 0)


#endif

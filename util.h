#ifndef _LIBTF2MOD_UTIL_H
#define _LIBTF2MOD_UTIL_H


uintptr_t calc_relative_jump(const func_t *func, size_t off, uintptr_t dst);

void mem_unprotect(const void *addr, size_t len);
void mem_protect(const void *addr, size_t len);

void func_unprotect(const func_t *func);
void func_protect(const func_t *func);

void mem_dump(const void *addr, size_t len, bool align);

void func_dump(const func_t *func);

uintptr_t find_string(const char *str);


#endif

#ifndef _LIBTF2MOD_SYMTAB_H
#define _LIBTF2MOD_SYMTAB_H


void symtab_init(library_info_t *lib);

void symtab_foreach(void (*callback)(const symbol_t *), Elf32_Word type);

bool symtab_lookup_name(library_info_t *lib, symbol_t *entry, Elf32_Word type,
	const char *name);
bool symtab_lookup_addr(library_info_t *lib, symbol_t *entry, Elf32_Word type,
	uintptr_t addr);
bool symtab_lookup_addr_range(library_info_t *lib, symbol_t *entry,
	Elf32_Word type, uintptr_t addr);

bool symtab_func_name(symbol_t *entry, const char *name);
bool symtab_func_addr_rel(symbol_t *entry, uintptr_t addr);
bool symtab_func_addr_abs(symbol_t *entry, uintptr_t addr);
bool symtab_func_addr_range_abs(symbol_t *entry, uintptr_t addr);

bool symtab_obj_name(symbol_t *entry, const char *name);
bool symtab_obj_addr_rel(symbol_t *entry, uintptr_t addr);
bool symtab_obj_addr_abs(symbol_t *entry, uintptr_t addr);

void symtab_obj_absolute(const char *name, void **addr, size_t *size);
void symtab_func_absolute(const char *name, void **addr, size_t *size);


#endif

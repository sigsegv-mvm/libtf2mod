#ifndef _LIBTF2MOD_SYMTAB_H
#define _LIBTF2MOD_SYMTAB_H


extern int         dl_fd;
extern struct stat dl_stat;
extern size_t      dl_size;
extern void       *dl_map;


void symtab_init(const char *dl_path);

void symtab_foreach(void (*callback)(const symbol_t *), Elf32_Word type);

bool symtab_lookup_name(symbol_t *entry, Elf32_Word type, const char *name);
bool symtab_lookup_addr(symbol_t *entry, Elf32_Word type, uintptr_t addr);

bool symtab_func_name(symbol_t *entry, const char *name);
bool symtab_func_addr(symbol_t *entry, uintptr_t addr);

bool symtab_obj_name(symbol_t *entry, const char *name);
bool symtab_obj_addr(symbol_t *entry, uintptr_t addr);


#endif

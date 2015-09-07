#include "all.h"


void symtab_init(library_info_t *lib)
{
	lib->elf_hdr = lib->map;
	lib->elf = elf_memory(lib->map, lib->size);
	
	Elf_Scn *scn = NULL;
	while ((scn = elf_nextscn(lib->elf, scn)) != NULL) {
		GElf_Shdr shdr;
		gelf_getshdr(scn, &shdr);
		
		char *scn_name = elf_strptr(lib->elf, lib->elf_hdr->e_shstrndx,
			shdr.sh_name);
		
		if (shdr.sh_type == SHT_SYMTAB) {
			if (strcmp(scn_name, ".symtab") == 0) {
				lib->symtab_shdr = shdr;
				lib->symtab_data = elf_getdata(scn, NULL);
				lib->symtab_count = shdr.sh_size / shdr.sh_entsize;
				//pr_debug("symtab_count: %u\n", lib->symtab_count);
			}
		} else if (shdr.sh_type == SHT_PROGBITS) {
			if (strcmp(scn_name, ".text") == 0) {
				//pr_debug("%s:%s %08x %08x\n", lib->name, scn_name,
				//	(uint32_t)shdr.sh_addr, (uint32_t)shdr.sh_size);
				lib->text_off  = shdr.sh_addr;
				lib->text_size = shdr.sh_size;
			} else if (strcmp(scn_name, ".data") == 0) {
				//pr_debug("%s:%s %08x %08x\n", lib->name, scn_name,
				//	(uint32_t)shdr.sh_addr, (uint32_t)shdr.sh_size);
				lib->data_off  = shdr.sh_addr;
				lib->data_size = shdr.sh_size;
			} else if (strcmp(scn_name, ".rodata") == 0) {
				//pr_debug("%s:%s %08x %08x\n", lib->name, scn_name,
				//	(uint32_t)shdr.sh_addr, (uint32_t)shdr.sh_size);
				lib->rodata_off  = shdr.sh_addr;
				lib->rodata_size = shdr.sh_size;
			} else if (strcmp(scn_name, ".data.rel.ro") == 0) {
				//pr_debug("%s:%s %08x %08x\n", lib->name, scn_name,
				//	(uint32_t)shdr.sh_addr, (uint32_t)shdr.sh_size);
				lib->datarelro_off  = shdr.sh_addr;
				lib->datarelro_size = shdr.sh_size;
			}
		} else if (shdr.sh_type == SHT_NOBITS) {
			if (strcmp(scn_name, ".bss") == 0) {
				//pr_debug("%s:%s %08x %08x\n", lib->name, scn_name,
				//	(uint32_t)shdr.sh_addr, (uint32_t)shdr.sh_size);
				lib->bss_off  = shdr.sh_addr;
				lib->bss_size = shdr.sh_size;
			}
		}
		
		/*pr_debug("type %08x flags %c%c%c%c name '%s'\n",
			shdr.sh_type,
			(shdr.sh_flags & SHF_WRITE     ? 'W' : ' '),
			(shdr.sh_flags & SHF_ALLOC     ? 'A' : ' '),
			(shdr.sh_flags & SHF_EXECINSTR ? 'X' : ' '),
			(shdr.sh_flags & SHF_STRINGS   ? 'S' : ' '),
			elf_strptr(lib->elf, lib->elf_hdr->e_shstrndx, shdr.sh_name));*/
	}
	
	
	//munmap(lib->map, lib->size);
	//close(lib->fd);
}


bool symtab_lookup_name(library_info_t *lib, symbol_t *entry, Elf32_Word type,
	const char *name)
{
	for (int i = 0; i < lib->symtab_count; ++i) {
		GElf_Sym sym;
		gelf_getsym(lib->symtab_data, i, &sym);
		
		if (ELF32_ST_TYPE(sym.st_info) != type) {
			continue;
		}
		
		const char *this_name =
			elf_strptr(lib->elf, lib->symtab_shdr.sh_link, sym.st_name);
		if (strcmp(this_name, name) == 0) {
			entry->lib  = lib;
			entry->addr = sym.st_value;
			entry->size = sym.st_size;
			entry->name = this_name;
			
			return true;
		}
		
		/*pr_debug("val %08x size %8x bind %2d type %2d name '%s'\n",
			val, size, bind, type,
			elf_strptr(lib->elf, shdr.sh_link, sym.st_name));*/
	}
	
	return false;
}

bool symtab_lookup_addr(library_info_t *lib, symbol_t *entry, Elf32_Word type,
	uintptr_t addr)
{
	for (int i = 0; i < lib->symtab_count; ++i) {
		GElf_Sym sym;
		gelf_getsym(lib->symtab_data, i, &sym);
		
		if (ELF32_ST_TYPE(sym.st_info) != type) {
			continue;
		}
		
		if (sym.st_value == addr) {
			entry->lib  = lib;
			entry->addr = sym.st_value;
			entry->size = sym.st_size;
			entry->name = elf_strptr(lib->elf,
				lib->symtab_shdr.sh_link, sym.st_name);
			
			return true;
		}
		
		/*fprintf(stderr,
			"val %08x size %8x bind %2d type %2d name '%s'\n",
			val, size, bind, type,
			elf_strptr(lib->elf, shdr.sh_link, sym.st_name));*/
	}
	
	return false;
}

bool symtab_lookup_addr_range(library_info_t *lib, symbol_t *entry,
	Elf32_Word type, uintptr_t addr)
{
	for (int i = 0; i < lib->symtab_count; ++i) {
		GElf_Sym sym;
		gelf_getsym(lib->symtab_data, i, &sym);
		
		if (ELF32_ST_TYPE(sym.st_info) != type) {
			continue;
		}
		
		if (addr >= sym.st_value &&
			addr < sym.st_value + sym.st_size) {
			//pr_debug("[%08llx <= %08x < %08llx]\n",
			//	sym.st_value, addr, sym.st_value + sym.st_size);
			
			entry->lib  = lib;
			entry->addr = sym.st_value;
			entry->size = sym.st_size;
			entry->name = elf_strptr(lib->elf,
				lib->symtab_shdr.sh_link, sym.st_name);
			
			return true;
		}
		
		/*fprintf(stderr,
			"val %08x size %8x bind %2d type %2d name '%s'\n",
			val, size, bind, type,
			elf_strptr(lib->elf, shdr.sh_link, sym.st_name));*/
	}
	
	return false;
}


bool symtab_func_name(symbol_t *entry, const char *name)
{
	library_info_t *lib = lib_first();
	
	do
	{
		if (symtab_lookup_name(lib, entry, STT_FUNC, name)) {
			return true;
		}
	} while ((lib = lib_next(lib)) != NULL);
	
	return false;
}

bool symtab_func_addr_rel(symbol_t *entry, uintptr_t addr)
{
	library_info_t *lib = lib_first();
	
	do
	{
		if (symtab_lookup_addr(lib, entry, STT_FUNC, addr)) {
			return true;
		}
	} while ((lib = lib_next(lib)) != NULL);
	
	return false;
}

bool symtab_func_addr_abs(symbol_t *entry, uintptr_t addr)
{
	library_info_t *lib = lib_first();
	
	do
	{
		if (addr >= lib->baseaddr && symtab_lookup_addr(lib, entry,
			STT_FUNC, addr - lib->baseaddr)) {
			return true;
		}
	} while ((lib = lib_next(lib)) != NULL);
	
	return false;
}

bool symtab_func_addr_range_abs(symbol_t *entry, uintptr_t addr)
{
	library_info_t *lib = lib_first();
	
	do
	{
		//pr_debug("lib %s addr %08x lib->baseaddr %08x\n",
		//	lib->name, addr, lib->baseaddr);
		if (addr >= lib->baseaddr && symtab_lookup_addr_range(lib, entry,
			STT_FUNC, addr - lib->baseaddr)) {
			return true;
		}
	} while ((lib = lib_next(lib)) != NULL);
	
	return false;
}


bool symtab_obj_name(symbol_t *entry, const char *name)
{
	library_info_t *lib = lib_first();
	
	do
	{
		if (symtab_lookup_name(lib, entry, STT_OBJECT, name)) {
			return true;
		}
	} while ((lib = lib_next(lib)) != NULL);
	
	return false;
}

bool symtab_obj_addr_rel(symbol_t *entry, uintptr_t addr)
{
	library_info_t *lib = lib_first();
	
	do
	{
		if (symtab_lookup_addr(lib, entry, STT_OBJECT, addr)) {
			return true;
		}
	} while ((lib = lib_next(lib)) != NULL);
	
	return false;
}

bool symtab_obj_addr_abs(symbol_t *entry, uintptr_t addr)
{
	library_info_t *lib = lib_first();
	
	do
	{
		if (addr >= lib->baseaddr &&
			symtab_lookup_addr(lib, entry, STT_OBJECT, addr - lib->baseaddr)) {
			return true;
		}
	} while ((lib = lib_next(lib)) != NULL);
	
	return false;
}


void symtab_obj_absolute(const char *name, void **addr, size_t *size)
{
	symbol_t sym;
	if (!symtab_obj_name(&sym, name)) {
		pr_warn("%s: failed for '%s'\n", __func__, name);
		return;
	}
	
	if (addr != NULL) {
		*addr = (void *)(sym.lib->baseaddr + sym.addr);
	}
	if (size != NULL) {
		*size = sym.size;
	}
}

void symtab_func_absolute(const char *name, void **addr, size_t *size)
{
	symbol_t sym;
	if (!symtab_func_name(&sym, name)) {
		pr_warn("%s: failed for '%s'\n", __func__, name);
		return;
	}
	
	if (addr != NULL) {
		*addr = (void *)(sym.lib->baseaddr + sym.addr);
	}
	if (size != NULL) {
		*size = sym.size;
	}
}

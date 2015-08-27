#include "all.h"


void symtab_init(library_info_t *lib)
{
	lib->elf_hdr = lib->map;
	lib->elf = elf_memory(lib->map, lib->size);
	
	Elf_Scn *scn = NULL;
	while ((scn = elf_nextscn(lib->elf, scn)) != NULL) {
		GElf_Shdr shdr;
		gelf_getshdr(scn, &shdr);
		
		if (shdr.sh_type == SHT_SYMTAB && strcmp(".symtab", elf_strptr(lib->elf,
			lib->elf_hdr->e_shstrndx, shdr.sh_name)) == 0) {
			lib->symtab_shdr = shdr;
			lib->symtab_data = elf_getdata(scn, NULL);
			lib->symtab_count = shdr.sh_size / shdr.sh_entsize;
			//pr_debug("symtab_count: %u\n", lib->symtab_count);
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


bool symtab_lookup_name(symbol_t *entry, Elf32_Word type, const char *name)
{
	library_info_t *lib = lib_first();
	
	do
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
	} while ((lib = lib_next(lib)) != NULL);
	
	return false;
}

bool symtab_lookup_addr(symbol_t *entry, Elf32_Word type, uintptr_t addr)
{
	library_info_t *lib = lib_first();
	
	do
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
	} while ((lib = lib_next(lib)) != NULL);
	
	return false;
}


bool symtab_func_name(symbol_t *entry, const char *name)
{
	return symtab_lookup_name(entry, STT_FUNC, name);
}

bool symtab_func_addr_rel(symbol_t *entry, uintptr_t addr)
{
	return symtab_lookup_addr(entry, STT_FUNC, addr);
}

bool symtab_func_addr_abs(symbol_t *entry, uintptr_t addr, const char *lib_name)
{
	library_info_t *lib = lib_find(lib_name);
	return symtab_lookup_addr(entry, STT_FUNC, addr - lib->baseaddr);
}

bool symtab_func_addr_abs_anylib(symbol_t *entry, uintptr_t addr)
{
	library_info_t *lib = lib_first();
	
	do
	{
		if (symtab_lookup_addr(entry, STT_FUNC, addr - lib->baseaddr)) {
			return true;
		}
	} while ((lib = lib_next(lib)) != NULL);
	
	return false;
}


bool symtab_obj_name(symbol_t *entry, const char *name)
{
	return symtab_lookup_name(entry, STT_OBJECT, name);
}

bool symtab_obj_addr_rel(symbol_t *entry, uintptr_t addr)
{
	return symtab_lookup_addr(entry, STT_OBJECT, addr);
}

bool symtab_obj_addr_abs(symbol_t *entry, uintptr_t addr, const char *lib_name)
{
	library_info_t *lib = lib_find(lib_name);
	return symtab_lookup_addr(entry, STT_OBJECT, addr - lib->baseaddr);
}

bool symtab_obj_addr_abs_anylib(symbol_t *entry, uintptr_t addr)
{
	library_info_t *lib = lib_first();
	
	do
	{
		if (symtab_lookup_addr(entry, STT_OBJECT, addr - lib->baseaddr)) {
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

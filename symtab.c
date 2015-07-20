#include "all.h"


int         dl_fd   = -1;
struct stat dl_stat;
size_t      dl_size = 0;
void       *dl_map  = NULL;

static Elf        *elf     = NULL;
static Elf32_Ehdr *elf_hdr = NULL;

static Elf_Data *symtab_data = NULL;
static GElf_Shdr symtab_shdr;
static int       symtab_count = 0;


void symtab_init(const char *dl_path)
{
	if ((dl_fd = open(dl_path, O_RDONLY)) == -1) {
		err(1, "open(server_srv.so) failed");
	}
	
	if (fstat(dl_fd, &dl_stat) != 0) {
		err(1, "fstat(server_srv.so) failed");
	}
	dl_size = dl_stat.st_size;
	
	if ((dl_map = mmap(NULL, dl_size, PROT_READ, MAP_PRIVATE, dl_fd, 0)) ==
		MAP_FAILED) {
		err(1, "mmap(server_srv.so) failed");
	}
	
	elf_hdr = dl_map;
	elf = elf_memory(dl_map, dl_size);
	
	Elf_Scn *scn = NULL;
	while ((scn = elf_nextscn(elf, scn)) != NULL) {
		GElf_Shdr shdr;
		gelf_getshdr(scn, &shdr);
		
		if (shdr.sh_type == SHT_SYMTAB && strcmp(".symtab",
			elf_strptr(elf, elf_hdr->e_shstrndx, shdr.sh_name)) == 0) {
			symtab_shdr = shdr;
			symtab_data = elf_getdata(scn, NULL);
			symtab_count = shdr.sh_size / shdr.sh_entsize;
			pr_debug("symtab_count: %u\n", symtab_count);
		}
		
		/*pr_debug("type %08x flags %c%c%c%c name '%s'\n",
			shdr.sh_type,
			(shdr.sh_flags & SHF_WRITE     ? 'W' : ' '),
			(shdr.sh_flags & SHF_ALLOC     ? 'A' : ' '),
			(shdr.sh_flags & SHF_EXECINSTR ? 'X' : ' '),
			(shdr.sh_flags & SHF_STRINGS   ? 'S' : ' '),
			elf_strptr(elf, elf_hdr->e_shstrndx, shdr.sh_name));*/
	}
	
	
	//munmap(dl_map, dl_size);
	//close(dl_fd);
}


void symtab_foreach(void (*callback)(const symbol_t *), Elf32_Word type)
{
	for (int i = 0; i < symtab_count; ++i)
	{
		GElf_Sym sym;
		gelf_getsym(symtab_data, i, &sym);
		
		if (ELF32_ST_TYPE(sym.st_info) != type) {
			continue;
		}
		
		symbol_t entry = {
			.addr = sym.st_value,
			.size = sym.st_size,
			.name = elf_strptr(elf, symtab_shdr.sh_link, sym.st_name),
		};
		callback(&entry);
	}
}


bool symtab_lookup_name(symbol_t *entry, Elf32_Word type, const char *name)
{
	for (int i = 0; i < symtab_count; ++i) {
		GElf_Sym sym;
		gelf_getsym(symtab_data, i, &sym);
		
		if (ELF32_ST_TYPE(sym.st_info) != type) {
			continue;
		}
		
		const char *this_name =
			elf_strptr(elf, symtab_shdr.sh_link, sym.st_name);
		if (strcmp(this_name, name) == 0) {
			entry->addr = sym.st_value;
			entry->size = sym.st_size;
			entry->name = this_name;
			
			return true;
		}
		
		/*pr_debug("val %08x size %8x bind %2d type %2d name '%s'\n",
			val, size, bind, type,
			elf_strptr(elf, shdr.sh_link, sym.st_name));*/
	}
	
	return false;
}

bool symtab_lookup_addr(symbol_t *entry, Elf32_Word type, uintptr_t addr)
{
	for (int i = 0; i < symtab_count; ++i) {
		GElf_Sym sym;
		gelf_getsym(symtab_data, i, &sym);
		
		if (ELF32_ST_TYPE(sym.st_info) != type) {
			continue;
		}
		
		if (sym.st_value == addr) {
			entry->addr = sym.st_value;
			entry->size = sym.st_size;
			entry->name = elf_strptr(elf, symtab_shdr.sh_link, sym.st_name);
			
			return true;
		}
		
		/*fprintf(stderr,
			"val %08x size %8x bind %2d type %2d name '%s'\n",
			val, size, bind, type,
			elf_strptr(elf, shdr.sh_link, sym.st_name));*/
	}
	
	return false;
}


bool symtab_func_name(symbol_t *entry, const char *name)
{
	return symtab_lookup_name(entry, STT_FUNC, name);
}

bool symtab_func_addr(symbol_t *entry, uintptr_t addr)
{
	return symtab_lookup_addr(entry, STT_FUNC, addr);
}


bool symtab_obj_name(symbol_t *entry, const char *name)
{
	return symtab_lookup_name(entry, STT_OBJECT, name);
}

bool symtab_obj_addr(symbol_t *entry, uintptr_t addr)
{
	return symtab_lookup_addr(entry, STT_OBJECT, addr);
}

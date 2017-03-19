#ifndef _LIBTF2MOD_UTIL_H
#define _LIBTF2MOD_UTIL_H


void mem_unprotect(const void *addr, size_t len);
void mem_protect(const void *addr, size_t len);

void func_unprotect(const func_t *func);
void func_protect(const func_t *func);

void mem_dump(const void *addr, size_t len, bool align);

void func_dump(const func_t *func);

uintptr_t find_string(const char *lib_name, const char *str, bool absolute);
uintptr_t find_string_global(const char *lib_name, const char *str,
	bool absolute);

const char *try_demangle(const char *mangled);

int64_t conv_timespec_to_nsec(const struct timespec *t);

int conv_EHANDLE_to_entindex(EHANDLE handle);

void cl_con_printf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

const char *get_string_for_damagebits(uint32_t m_bitsDamageType);
const char *get_string_for_customkill(int m_iCustomKill);
const char *get_string_for_weaponid(int id);
const char *get_string_for_condition(ETFCond cond);


static inline edict_t* INDEXENT(int iEdictNum)
{
	return CVEngineServer_PEntityOfEntIndex(*engine, iEdictNum);
}

static inline CBaseEntity* GetContainingEntity(edict_t* pent)
{
	if (pent != NULL && pent->base.m_pUnk != NULL) {
		return vcall_IServerUnknown_GetBaseEntity(pent->base.m_pUnk);
	}
	
	return NULL;
}

static inline CBaseEntity* CBaseEntity_Instance(edict_t* pent)
{
	if (pent == NULL) {
		pent = INDEXENT(0);
	}
	
	return GetContainingEntity(pent);
}


extern void *__dynamic_cast(const void *__src_ptr,
	const void *__src_type,
	const void *__dst_type,
	ptrdiff_t __src2dst);

void *__dynamic_cast_NULL_safe(const void *__src_ptr,
	const void *__src_type,
	const void *__dst_type,
	ptrdiff_t __src2dst);

#define DYNAMIC_CAST(_src, _src_type, _dst_type) \
	__dynamic_cast_NULL_safe(_src, typeinfo_for_ ## _src_type, typeinfo_for_ ## _dst_type, -1)


extern void *_Znwj(size_t n);
#define OPERATOR_NEW(_n) _Znwj(_n)


#endif

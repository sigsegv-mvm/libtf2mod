#include "all.h"


DETOUR(debug_multidamage);
/*  */


static void (*trampoline_ClearMultiDamage)(void);
static void (*trampoline_ApplyMultiDamage)(void);
static void (*trampoline_AddMultiDamage)(CTakeDamageInfo const*, CBaseEntity*);


// 1: enable
// 2: backtrace
static ConVar cvar_ClearMultiDamage;
static ConVar cvar_ApplyMultiDamage;
static ConVar cvar_AddMultiDamage;


static void detour_ClearMultiDamage(void)
{
	int cvar = ConVar_GetInt(&cvar_ClearMultiDamage);
	if ((cvar & 1) == 0) goto done;
	
	cl_con_printf("[%8.3f] ClearMultiDamage()\n",
		(*gpGlobals)->curtime);
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_ClearMultiDamage();
}

static void detour_ApplyMultiDamage(void)
{
	int cvar = ConVar_GetInt(&cvar_ApplyMultiDamage);
	if ((cvar & 1) == 0) goto done;
	
	cl_con_printf("[%8.3f] ApplyMultiDamage()\n",
		(*gpGlobals)->curtime);
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_ApplyMultiDamage();
}

static void detour_AddMultiDamage(CTakeDamageInfo const* info, CBaseEntity* pEntity)
{
	int cvar = ConVar_GetInt(&cvar_AddMultiDamage);
	if ((cvar & 1) == 0) goto done;
	
	cl_con_printf("[%8.3f] AddMultiDamage(<info>, %d)\n",
		(*gpGlobals)->curtime, ENTINDEX(pEntity));
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_AddMultiDamage(info, pEntity);
}


#define SYM_AND_DETOUR(_var, _mangled) \
	void *_var; \
	symtab_func_absolute(_mangled, (void **)&_var, NULL); \
	DETOUR_CREATE(_var)


DETOUR_SETUP
{
	ConVar_ctor(&cvar_ClearMultiDamage,
		"sigsegv_debug_ClearMultiDamage", "1", FCVAR_NOTIFY,
		"Debug: trace calls to ClearMultiDamage");
	ConVar_ctor(&cvar_ApplyMultiDamage,
		"sigsegv_debug_ApplyMultiDamage", "1", FCVAR_NOTIFY,
		"Debug: trace calls to ApplyMultiDamage");
	ConVar_ctor(&cvar_AddMultiDamage,
		"sigsegv_debug_AddMultiDamage", "1", FCVAR_NOTIFY,
		"Debug: trace calls to AddMultiDamage");
	
	SYM_AND_DETOUR(ClearMultiDamage, "_Z16ClearMultiDamagev");
	SYM_AND_DETOUR(ApplyMultiDamage, "_Z16ApplyMultiDamagev");
	SYM_AND_DETOUR(AddMultiDamage, "_Z14AddMultiDamageRK15CTakeDamageInfoP11CBaseEntity");
	
	return true;
}

#include "all.h"


DETOUR(debug_wavestatus_tele_count);
/*  */


static unknown_t (*trampoline_CTFObjectiveResource_DecrementTeleporterCount)(CTFObjectiveResource* this);
static unknown_t (*trampoline_CTFObjectiveResource_IncrementTeleporterCount)(CTFObjectiveResource* this);


// 1: enable
// 2: backtrace
static ConVar cvar_CTFObjectiveResource_DecrementTeleporterCount;
static ConVar cvar_CTFObjectiveResource_IncrementTeleporterCount;


static void _get_ent_info(CBaseEntity* ent, char *dst, size_t len)
{
	if (ent == NULL) {
		strlcpy(dst, "nullptr", len);
	} else {
		const char *m_iClassname = *prop_CBaseEntity_m_iClassname(ent);
		const char *m_iName = *prop_CBaseEntity_m_iName(ent);
		
		snprintf(dst, len,
			"0x%08x[#%d class:\"%s\" name:\"%s\"]",
			(uintptr_t)ent,
			ENTINDEX(ent),
			(m_iClassname != NULL ? m_iClassname : ""),
			(m_iName != NULL ? m_iName : ""));
	}
}


static unknown_t detour_CTFObjectiveResource_DecrementTeleporterCount(CTFObjectiveResource* this)
{
	int cvar = ConVar_GetInt(&cvar_CTFObjectiveResource_DecrementTeleporterCount);
	if ((cvar & 1) == 0) goto done;
	
	/* get the caller's CObjectTeleporter* this */
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	CObjectTeleporter* caller_this = *(CObjectTeleporter**)(caller_frame + 8);
	int objidx = ENTINDEX(caller_this);
	
	char str_this[4096];
	_get_ent_info(caller_this, str_this, sizeof(str_this));
	cl_con_printf("[%8.3f] CTFObjectiveResource::DecrementTeleporterCount() for tele %s\n",
		(*gpGlobals)->curtime, str_this);
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_CTFObjectiveResource_DecrementTeleporterCount(this);
}

static unknown_t detour_CTFObjectiveResource_IncrementTeleporterCount(CTFObjectiveResource* this)
{
	int cvar = ConVar_GetInt(&cvar_CTFObjectiveResource_IncrementTeleporterCount);
	if ((cvar & 1) == 0) goto done;
	
	/* get the caller's CObjectTeleporter* this */
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	CObjectTeleporter* caller_this = *(CObjectTeleporter**)(caller_frame + 8);
	int objidx = ENTINDEX(caller_this);
	
	char str_this[4096];
	_get_ent_info(caller_this, str_this, sizeof(str_this));
	cl_con_printf("[%8.3f] CTFObjectiveResource::IncrementTeleporterCount() for tele %s\n",
		(*gpGlobals)->curtime, str_this);
	
	if ((cvar & 2) == 0) goto done;
	BACKTRACE_CL_CON_EX("           ", 1);
	
done:
	return trampoline_CTFObjectiveResource_IncrementTeleporterCount(this);
}


DETOUR_SETUP
{
	ConVar_ctor(&cvar_CTFObjectiveResource_DecrementTeleporterCount,
		"sigsegv_debug_CTFObjectiveResource_DecrementTeleporterCount", "0", FCVAR_NOTIFY,
		"Debug: trace calls to CTFObjectiveResource::DecrementTeleporterCount");
	ConVar_ctor(&cvar_CTFObjectiveResource_IncrementTeleporterCount,
		"sigsegv_debug_CTFObjectiveResource_IncrementTeleporterCount", "0", FCVAR_NOTIFY,
		"Debug: trace calls to CTFObjectiveResource::IncrementTeleporterCount");
	
	DETOUR_CREATE(CTFObjectiveResource_DecrementTeleporterCount);
	DETOUR_CREATE(CTFObjectiveResource_IncrementTeleporterCount);
	
	return true;
}

#include "all.h"


DETOUR(debug_addcond_removecond);
/*  */


static void (*trampoline_CTFPlayerShared_AddCond)(CTFPlayerShared* this, ETFCond, float, CBaseEntity*);
static void (*trampoline_CTFPlayerShared_RemoveCond)(CTFPlayerShared* this, ETFCond, bool);


static ConVar cvar_sigsegv_debug_addcond_removecond;
static ConVar cvar_sigsegv_debug_addcond_removecond_filter;
static ConVar cvar_sigsegv_debug_addcond_removecond_backtrace;
static ConVar cvar_sigsegv_debug_addcond_removecond_ignore115;


static void detour_CTFPlayerShared_AddCond(CTFPlayerShared* this, ETFCond cond, float duration, CBaseEntity* provider)
{
	if (ConVar_GetInt(&cvar_sigsegv_debug_addcond_removecond) != 0) {
		if (cond != 115 || ConVar_GetInt(&cvar_sigsegv_debug_addcond_removecond_ignore115) == 0) {
			int filter = ConVar_GetInt(&cvar_sigsegv_debug_addcond_removecond_filter);
			if (filter == -1 || cond == filter) {
				CTFPlayer **player = prop_CTFPlayerShared_m_pOuter(this);
				char *netname = prop_CTFPlayer_m_szNetname(*player);
				
				cl_con_printf(">> [%8.3f] AddCond('%s', %d TF_COND_%s, %.2f sec, provider #%d)\n",
					(*gpGlobals)->curtime, netname, cond, get_string_for_condition(cond), duration, ENTINDEX(provider));
				if (ConVar_GetInt(&cvar_sigsegv_debug_addcond_removecond_backtrace) != 0) {
					BACKTRACE_CL_CON();
				}
			}
		}
	}
	
	trampoline_CTFPlayerShared_AddCond(this, cond, duration, provider);
}

static void detour_CTFPlayerShared_RemoveCond(CTFPlayerShared* this, ETFCond cond, bool b1)
{
	if (ConVar_GetInt(&cvar_sigsegv_debug_addcond_removecond) != 0) {
		if (cond != 115 || ConVar_GetInt(&cvar_sigsegv_debug_addcond_removecond_ignore115) == 0) {
			int filter = ConVar_GetInt(&cvar_sigsegv_debug_addcond_removecond_filter);
			if (filter == -1 || cond == filter) {
				CTFPlayer **player = prop_CTFPlayerShared_m_pOuter(this);
				char *netname = prop_CTFPlayer_m_szNetname(*player);
				
				cl_con_printf(">> [%8.3f] RemoveCond('%s', %d TF_COND_%s, %s)\n",
					(*gpGlobals)->curtime, netname, cond, get_string_for_condition(cond), (b1 ? "TRUE" : "FALSE"));
				if (ConVar_GetInt(&cvar_sigsegv_debug_addcond_removecond_backtrace) != 0) {
					BACKTRACE_CL_CON();
				}
			}
		}
	}
	
	trampoline_CTFPlayerShared_RemoveCond(this, cond, b1);
}


DETOUR_SETUP
{
	ConVar_ctor(&cvar_sigsegv_debug_addcond_removecond,
		"sigsegv_debug_addcond_removecond", "0", FCVAR_NOTIFY,
		"Debug: trace calls to CTFPlayerShared::AddCond and ::RemoveCond");
	ConVar_ctor(&cvar_sigsegv_debug_addcond_removecond_filter,
		"sigsegv_debug_addcond_removecond_filter", "-1", FCVAR_NOTIFY,
		"Debug: if not -1, only show calls for this cond");
	ConVar_ctor(&cvar_sigsegv_debug_addcond_removecond_backtrace,
		"sigsegv_debug_addcond_removecond_backtrace", "0", FCVAR_NOTIFY,
		"Debug: spew backtrace from every addcond/removecond");
	ConVar_ctor(&cvar_sigsegv_debug_addcond_removecond_ignore115,
		"sigsegv_debug_addcond_removecond_ignore115", "1", FCVAR_NOTIFY,
		"Debug: ignore cond 115 spam from 20151217 update");
	
	DETOUR_CREATE(CTFPlayerShared_AddCond);
	DETOUR_CREATE(CTFPlayerShared_RemoveCond);
	
	return true;
}

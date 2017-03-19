#include "all.h"


DETOUR(debug_sentry_dmg_kills);
/*  */


static ConVar cvar_sentry_dmg_offset;
static ConVar cvar_sentry_kills_offset;

static ConCommand ccmd_show_sentry_dmg;
static ConCommand ccmd_show_sentry_kills;


static void do_ccmd_show_sentry_dmg(const CCommand *arg)
{
	const char *player_name = CCommand_Arg(arg, 1);
	if (strcmp(player_name, "") == 0) {
		return;
	}
	
	CTFPlayer* player = UTIL_PlayerByName(player_name);
	if (player == NULL) {
		return;
	}
	
	long offset = strtol(ConVar_GetString(&cvar_sentry_dmg_offset), NULL, 0);
	if (offset == 0) {
		return;
	}
	
	float *m_flSentryDamage = (float *)((uintptr_t)player + offset);
	cl_con_printf("%s: m_flSentryDamage = %.0f\n",
		player_name, *m_flSentryDamage);
}

static void do_ccmd_show_sentry_kills(const CCommand *arg)
{
	const char *player_name = CCommand_Arg(arg, 1);
	if (strcmp(player_name, "") == 0) {
		return;
	}
	
	CTFPlayer* player = UTIL_PlayerByName(player_name);
	if (player == NULL) {
		return;
	}
	
	long offset = strtol(ConVar_GetString(&cvar_sentry_kills_offset), NULL, 0);
	if (offset == 0) {
		return;
	}
	
	int *m_nSentryKills = (int *)((uintptr_t)player + offset);
	cl_con_printf("%s: m_nSentryKills   = %d\n",
		player_name, *m_nSentryKills);
}


DETOUR_SETUP
{
	ConVar_ctor(&cvar_sentry_dmg_offset,
		"sigsegv_debug_sentry_dmg_offset", "0x2278", FCVAR_NOTIFY,
		"Debug: offset of CTFPlayer::m_flSentryDamage");
	ConVar_ctor(&cvar_sentry_kills_offset,
		"sigsegv_debug_sentry_kills_offset", "0x227c", FCVAR_NOTIFY,
		"Debug: offset of CTFPlayer::m_nSentryKills");
	
	ConCommand_ctor(&ccmd_show_sentry_dmg,
		"sigsegv_debug_show_sentry_dmg", do_ccmd_show_sentry_dmg,
		"Debug: show current value of CTFPlayer::m_flSentryDamage",
		FCVAR_NONE, NULL);
	ConCommand_ctor(&ccmd_show_sentry_kills,
		"sigsegv_debug_show_sentry_kills", do_ccmd_show_sentry_kills,
		"Debug: show current value of CTFPlayer::m_nSentryKills",
		FCVAR_NONE, NULL);
	
	return true;
}

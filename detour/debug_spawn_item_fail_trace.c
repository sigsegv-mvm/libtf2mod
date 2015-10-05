#include "all.h"


DETOUR(debug_spawn_item_fail_trace);
/*  */


static CBaseEntity* (*trampoline_CTFPlayer_GiveNamedItem)(CTFPlayer* this, char const*, int, CEconItemView const*, bool);
static CBaseEntity* (*trampoline_CBasePlayer_GiveNamedItem)(CBasePlayer* this, char const*, int);


static CBaseEntity* detour_CTFPlayer_GiveNamedItem(CTFPlayer* this, char const* s1, int i1, CEconItemView const* view, bool b1)
{
	CBaseEntity* result = trampoline_CTFPlayer_GiveNamedItem(this, s1, i1, view, b1);
	
	if (result == NULL) {
		pr_warn("CTFPlayer::GiveNamedItem('%s', %d) returned NULL!\n",
			s1, i1);
		BACKTRACE();
	}
	
	return result;
}

static CBaseEntity* detour_CBasePlayer_GiveNamedItem(CBasePlayer* this, char const* s1, int i1)
{
	CBaseEntity* result = trampoline_CBasePlayer_GiveNamedItem(this, s1, i1);
	
	if (result == NULL) {
		pr_warn("CBasePlayer::GiveNamedItem('%s', %d) returned NULL!\n",
			s1, i1);
		BACKTRACE();
	}
	
	return result;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_GiveNamedItem);
	DETOUR_CREATE(CBasePlayer_GiveNamedItem);
	
	return true;
}

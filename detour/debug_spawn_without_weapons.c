#include "all.h"


DETOUR(debug_spawn_without_weapons);
/*  */


static unknown_t (*trampoline_CTFPlayer_GiveNamedItem)(CTFPlayer* this, char const*, int, CEconItemView const*, bool);
static unknown_t (*trampoline_CBasePlayer_GiveNamedItem)(CBasePlayer* this, char const*, int);


static unknown_t detour_CTFPlayer_GiveNamedItem(CTFPlayer* this, char const* s1, int i1, CEconItemView const* view, bool b1)
{
	pr_info("CTFPlayer::GiveNamedItem\n");
	pr_debug(
		"  player entindex: %d\n"
		"  s1:              '%s'\n"
		"  i1:              %d\n"
		"  b1:              %s\n",
		ENTINDEX(this),
		s1,
		i1,
		(b1 ? "TRUE" : "FALSE"));
	
	
	return (unknown_t)NULL;
	//return trampoline_CTFPlayer_GiveNamedItem(this, s1, i1, view, b1);
}

static unknown_t detour_CBasePlayer_GiveNamedItem(CBasePlayer* this, char const* s1, int i1)
{
	pr_info("CBasePlayer::GiveNamedItem\n");
	pr_debug(
		"  player entindex: %d\n"
		"  s1:              '%s'\n"
		"  i1:              %d\n",
		ENTINDEX(this),
		s1,
		i1);
	
	
	return (unknown_t)NULL;
	//return trampoline_CBasePlayer_GiveNamedItem(this, s1, i1);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_GiveNamedItem);
	DETOUR_CREATE(CBasePlayer_GiveNamedItem);
}

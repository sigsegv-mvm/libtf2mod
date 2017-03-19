#include "all.h"


DETOUR(demoshield_tank_killeater_cheat);
/*  */


static void (*trampoline_EconEntity_OnOwnerKillEaterEventNoPartner)(CEconEntity*, CTFPlayer*, int, int);


static void detour_EconEntity_OnOwnerKillEaterEventNoPartner(CEconEntity* item, CTFPlayer* player, int eventid, int increment)
{
	pr_debug("EconEntity_OnOwnerKillEaterEventNoPartner"
		"(event %d, increment %d)\n",
		eventid, increment);
	
	if (eventid == 61 && player != NULL) {
		CTFWearableDemoShield* shield = GetEquippedDemoShield(player);
		if (shield != NULL) {
			pr_info("  intercepting killeater event 61!\n");
			//item = shield;
			increment = 1000000;
		}
	}
	
	trampoline_EconEntity_OnOwnerKillEaterEventNoPartner(item, player, eventid, increment);
}


DETOUR_SETUP
{
	DETOUR_CREATE(EconEntity_OnOwnerKillEaterEventNoPartner);
	
	return true;
}

#include "all.h"


DETOUR(pushallplayersaway_disable);
/* disable the functionality of CTFGameRules::PushAllPlayersAway
 * (used by engiebot behaviors to push players when they spawn and build) */


static void (*trampoline_CTFGameRules_PushAllPlayersAway)(void*);


void detour_CTFGameRules_PushAllPlayersAway(void* this)
{
	/* only run the function every third time */
	static int c = 0;
	if (c == 0) {
		trampoline_CTFGameRules_PushAllPlayersAway(this);
	}
	if (++c == 3) {
		c = 0;
	}
}


DETOUR_SETUP
{
	func_t *func1 = func_register(
		"_ZN12CTFGameRules18PushAllPlayersAwayERK6VectorffiP10CUtlVectorIP9CTFPlayer10CUtlMemoryIS5_iEE");
	
	
	/* CTFGameRules::PushAllPlayersAway(Vector const&, float, float, int, CUtlVector<CTFPlayer*, CUtlMemory<CTFPlayer*, int> >*) */
	trampoline_CTFGameRules_PushAllPlayersAway =
		(void *)(func1->trampoline_addr);
	
	
	func_detour_enable(func1,
		&detour_CTFGameRules_PushAllPlayersAway);
}

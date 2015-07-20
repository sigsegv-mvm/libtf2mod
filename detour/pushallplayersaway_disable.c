#include "all.h"


DETOUR(pushallplayersaway_disable);
/* disable the functionality of CTFGameRules::PushAllPlayersAway
 * (used by engiebot behaviors to push players when they spawn and build) */


static void (*trampoline_CTFGameRules_PushAllPlayersAway)(void*, void*, float, float, int, void*);


void detour_CTFGameRules_PushAllPlayersAway(void* this, void* loc, float f1, float f2, int i1, void* players)
{
	/* do absolutely nothing */
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

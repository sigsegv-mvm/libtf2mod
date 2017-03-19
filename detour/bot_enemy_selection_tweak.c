#include "all.h"


DETOUR(bot_enemy_selection_tweak);
/*  */


static CTFPlayer* (*trampoline_CTFBot_SelectRandomReachableEnemy)(CTFBot* this);


static CTFPlayer* detour_CTFBot_SelectRandomReachableEnemy(CTFBot* this)
{
	return NULL;
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFBot_SelectRandomReachableEnemy);
	
	return true;
}

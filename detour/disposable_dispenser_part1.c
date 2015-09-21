#include "all.h"


DETOUR(disposable_dispenser_part1);
/* allows the build menu to build a disposable dispenser */


static int (*trampoline_CTFPlayer_CanBuild)(CTFPlayer* this, int, int);


static int detour_CTFPlayer_CanBuild(CTFPlayer* this, int type, int subtype)
{
	int result = trampoline_CTFPlayer_CanBuild(this, type, subtype);
	
	// results:
	// 5: if type > 3
	// 2: if type == 1 and CTFPlayer::GetNumObjects(3, -1) == 0
	// 0/1: teleporter ammo count
	// 1: if !CTFPlayerClassShared::CanBuildObject(type)
	// 0: if object already exists and object->byte_0x0a0c != 0
	// 0/1: 
	
	pr_debug("%s: type %d subtype %d result %d\n",
		__func__, type, subtype, result);
	
	if (type == 0 && result != 0) {
		// TEMPORARY HACK!
		pr_debug("%s: result was %d, returning 0!\n",
			__func__, result);
		result = 0;
		
		// check CTFPlayerClassShared::CanBuildObject(0) 
		// - IMPORTANT: add 26a8 to this ptr!
		// get gp_GameRules
		// call CTFGameRules::IsPVEModeActive()
		
		// call CTFPlayer::GetObjectCount()
		// set num_of_disposable_dispensers = 0
		// for i = 0 to count-1:
		//   call CTFPlayer::GetObject(i)
		//   if null, continue
		//   if CBaseObject::GetType() != 0, continue
		//   if object->byte_0xa0f == 1, ++num_of_disposable_dispensers
		// if num_of_disposable_dispensers < max_disposable_dispensers
		
		// ebp-0x24: number of disposable sentries allowed
		// ebp-0x1c: number of current disposable sentries
		
		// if all succeeds, then set result to zero
	}
	
	return result;
	
	// POSSIBLE BUG:
	// CTFPlayer::CanBuild logic for disposable sentries may count disposable
	// dispensers toward its limit because it only checks offset 0xa0f, not the
	// type of object
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_CanBuild);
	
	return true;
}

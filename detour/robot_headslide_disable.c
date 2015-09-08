#include "all.h"


DETOUR(robot_headslide_disable);
/* remove the push force imparted on you when standing on a robot's head */


static unknown_t (*trampoline_CTFPlayer_ApplyAbsVelocityImpulse)(CTFPlayer* this, Vector const*);


static func_t *func_CTFPlayer_TFPlayerThink;


static unknown_t detour_CTFPlayer_ApplyAbsVelocityImpulse(CTFPlayer* this, Vector const* vec)
{
	uintptr_t caller = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	uintptr_t caller_frame = (uintptr_t)__builtin_frame_address(1);
	
	/* CTFPlayer::TFPlayerThink only calls this function for MvM robot head
	 * sliding purposes, so we can safely ignore its calls */
	if (func_owns_addr(caller,
		func_CTFPlayer_TFPlayerThink)) {
		return 0;
	}
	
	return trampoline_CTFPlayer_ApplyAbsVelocityImpulse(this, vec);
}


DETOUR_SETUP
{
	func_CTFPlayer_TFPlayerThink =
		func_register(CTFPlayer_TFPlayerThink);
	
	
	DETOUR_CREATE(CTFPlayer_ApplyAbsVelocityImpulse);
}

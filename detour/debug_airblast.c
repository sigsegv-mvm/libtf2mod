#include "all.h"


DETOUR(debug_airblast);
/*  */


static void (*trampoline_CTFPlayer_ApplyAirBlastImpulse)(CTFPlayer* this, Vector const*);
static void (*trampoline_CTFPlayer_ApplyAbsVelocityImpulse)(CTFPlayer* this, Vector const*);
static void (*trampoline_CBaseEntity_ApplyAbsVelocityImpulse)(CBaseEntity* this, Vector const*);


static func_t *func_CTFPlayer_ApplyAbsVelocityImpulse;


static void detour_CTFPlayer_ApplyAirBlastImpulse(CTFPlayer* this, Vector const* vec)
{
	pr_info("\nCTFPlayer::ApplyAirBlastImpulse       ");
	pr_debug(" %08x [ %+6.1f  %+6.1f  %+6.1f ]\n",
		(uintptr_t)this,
		vec->x,
		vec->y,
		vec->z);
	
	trampoline_CTFPlayer_ApplyAirBlastImpulse(this, vec);
}

static void detour_CTFPlayer_ApplyAbsVelocityImpulse(CTFPlayer* this, Vector const* vec)
{
	pr_info("CTFPlayer::ApplyAbsVelocityImpulse      ");
	pr_debug(" %08x [ %+6.1f  %+6.1f  %+6.1f ]\n",
		(uintptr_t)this,
		vec->x,
		vec->y,
		vec->z);
	
	trampoline_CTFPlayer_ApplyAbsVelocityImpulse(this, vec);
}

static void detour_CBaseEntity_ApplyAbsVelocityImpulse(CBaseEntity* this, Vector const* vec)
{
	uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
		__builtin_return_address(0));
	
	if (func_owns_addr(caller1,
		func_CTFPlayer_ApplyAbsVelocityImpulse)) {
		pr_info("CBaseEntity::ApplyAbsVelocityImpulse");
		pr_debug(" %08x [ %+6.1f  %+6.1f  %+6.1f ]\n",
			(uintptr_t)this,
			vec->x,
			vec->y,
			vec->z);
	}
	
	trampoline_CBaseEntity_ApplyAbsVelocityImpulse(this, vec);
}


DETOUR_SETUP
{
	func_CTFPlayer_ApplyAbsVelocityImpulse =
		func_register(CTFPlayer_ApplyAbsVelocityImpulse);
	
	DETOUR_CREATE(CTFPlayer_ApplyAirBlastImpulse);
	DETOUR_CREATE(CTFPlayer_ApplyAbsVelocityImpulse);
	DETOUR_CREATE(CBaseEntity_ApplyAbsVelocityImpulse);
	
	return true;
}

#include "all.h"


DETOUR(debug_gib_glitch);
/*  */


static void (*trampoline_CTFPlayer_CreateRagdollEntity)(CTFPlayer* this, bool, bool, bool, bool, bool, bool, bool, bool, int, bool);


static void detour_CTFPlayer_CreateRagdollEntity(CTFPlayer* this,
//	bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7, bool b8, int i1, bool b9)
	uint32_t b1, uint32_t b2, uint32_t b3, uint32_t b4, uint32_t b5, uint32_t b6, uint32_t b7, uint32_t b8, int i1, uint32_t b9)
{
	int entindex = ENTINDEX(this);
	if (entindex == 0) {
		pr_debug("%s: ENTINDEX(%08x) = 0\n", __func__, (uintptr_t)this);
	}
	
	pr_info("CTFPlayer::CreateRagdollEntity\n");
	pr_debug(
		"  player entindex:      %d\n"
		"  b1 (ShouldGib):       %x\n"
		"  b2 (pyro on fire):    %x\n"
		"  b3 (medic uber drop): %x\n"
		"  b4 (FL_ONGROUND):     %x\n"
		"  b5 (YER disguise):    %x\n"
		"  b6 (Saxxy):           %x\n"
		"  b7 (Spy-Cicle):       %x\n"
		"  b8 (pyro DRG ash):    %x\n"
		"  i1 (m_iDamageCustom): %d\n"
		"  b9 (Classic gib):     %x\n",
		entindex,
		/*(b1 ? "TRUE" : "FALSE"),
		(b2 ? "TRUE" : "FALSE"),
		(b3 ? "TRUE" : "FALSE"),
		(b4 ? "TRUE" : "FALSE"),
		(b5 ? "TRUE" : "FALSE"),
		(b6 ? "TRUE" : "FALSE"),
		(b7 ? "TRUE" : "FALSE"),
		(b8 ? "TRUE" : "FALSE"),*/
		b1, b2, b2, b4, b5, b6, b7, b8,
		i1,
		b9
		/*(b9 ? "TRUE" : "FALSE")*/);
	
	trampoline_CTFPlayer_CreateRagdollEntity(this, b1, b2, b3, b4, b5, b6, b7, b8, i1, b9);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFPlayer_CreateRagdollEntity);
}

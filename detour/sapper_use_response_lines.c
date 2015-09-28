#include "all.h"


DETOUR(sapper_use_response_lines);
/* when sapping a robot, instead of speaking TLK_STUNNED_TARGET, speak
 * TLK_MVM_SAPPED_ROBOT, which will cause the spy to use the unused voice
 * lines for "sapping a robot" if disguised as soldier/heavy/engie/medic */


static unknown_t (*trampoline_CTFPlayer_SpeakConceptIfAllowed)(CTFPlayer* this, int, char const*, char*, unsigned int, IRecipientFilter*);


static func_t *func_CTFPlayerShared_StunPlayer;
static func_t *func_CObjectSapper_ApplyRoboSapperEffects;


static unknown_t detour_CTFPlayer_SpeakConceptIfAllowed(CTFPlayer* this, int concept, char const* s1, char* s2, unsigned int i1, IRecipientFilter* f)
{
	if (concept == TLK_STUNNED_TARGET) {
		uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(0));
		uintptr_t caller2 = (uintptr_t)__builtin_extract_return_addr(
			__builtin_return_address(1));
		
		if (func_owns_addr(caller1,
			func_CTFPlayerShared_StunPlayer) &&
			func_owns_addr(caller2,
			func_CObjectSapper_ApplyRoboSapperEffects)) {
			concept = TLK_MVM_SAPPED_ROBOT;
		}
	}
	
	return trampoline_CTFPlayer_SpeakConceptIfAllowed(this, concept, s1, s2, i1, f);
}


DETOUR_SETUP
{
	func_CTFPlayerShared_StunPlayer =
		func_register(CTFPlayerShared_StunPlayer);
	func_CObjectSapper_ApplyRoboSapperEffects =
		func_register(CObjectSapper_ApplyRoboSapperEffects);
	
	DETOUR_CREATE(CTFPlayer_SpeakConceptIfAllowed);
	
	return true;
}

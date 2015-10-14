#include "all.h"


DETOUR(shared_CTFPlayer_SpeakConceptIfAllowed);
/* shared detour for CTFPlayer::SpeakConceptIfAllowed */


static unknown_t (*trampoline_CTFPlayer_SpeakConceptIfAllowed)(CTFPlayer* this, int, char const*, char*, unsigned int, IRecipientFilter*);


static func_t *func_CTFPlayerShared_StunPlayer;
static func_t *func_CObjectSapper_ApplyRoboSapperEffects;
static func_t *func_CCurrencyPack_MyTouch;


static unknown_t detour_CTFPlayer_SpeakConceptIfAllowed(CTFPlayer* this, int concept, char const* s1, char* s2, unsigned int i1, IRecipientFilter* f)
{
	if (detour_responses_sapper.ok) {
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
	}
	
	
	if (detour_responses_credits.ok) {
		if (concept == TLK_MVM_MONEY_PICKUP) {
			uintptr_t caller1 = (uintptr_t)__builtin_extract_return_addr(
				__builtin_return_address(0));
			
			if (func_owns_addr(caller1,
				func_CCurrencyPack_MyTouch)) {
				/* find a better way to do this */
				int r = rand() % 4;
				
				int *m_iClass = prop_CTFPlayer_m_iClass(this);
				if (*m_iClass == TFCLASS_HEAVY || *m_iClass == TFCLASS_ENGINEER) {
					concept = TLK_MVM_ENCOURAGE_MONEY;
				} else if (*m_iClass == TFCLASS_SOLDIER) {
					if (r < 2) {
						concept = TLK_MVM_ENCOURAGE_MONEY;
					}
				} else if (*m_iClass == TFCLASS_MEDIC) {
					if (r < 3) {
						concept = TLK_MVM_ENCOURAGE_MONEY;
					}
				}
			}
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
	func_CCurrencyPack_MyTouch =
		func_register(CCurrencyPack_MyTouch);
	
	DETOUR_CREATE(CTFPlayer_SpeakConceptIfAllowed);
	
	return true;
}

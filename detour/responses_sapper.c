#include "all.h"


DETOUR(responses_sapper);
/* when sapping a robot, instead of speaking TLK_STUNNED_TARGET, speak
 * TLK_MVM_SAPPED_ROBOT, which will cause the spy to use the unused voice
 * lines for "sapping a robot" if disguised as soldier/heavy/engie/medic */


DETOUR_SETUP
{
	/* this detour is actually implemented in the shared detour for
	 * CTFPlayer::SpeakConceptIfAllowed */
	
	return true;
}

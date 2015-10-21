#include "all.h"


DETOUR(responses_suppress_medicbot_shield);
/* when a medicbot activates the medigun shield, suppress the voice line: it has
 * no robot version, so the medicbot speaks like a human */


DETOUR_SETUP
{
	/* this detour is actually implemented in the shared detour for
	 * CTFPlayer::SpeakConceptIfAllowed */
	
	return true;
}

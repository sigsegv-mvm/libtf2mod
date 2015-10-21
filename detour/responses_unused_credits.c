#include "all.h"


DETOUR(responses_unused_credits);
/* add a chance to say TLK_MVM_ENCOURAGE_MONEY when credits are picked up by
 * soldier, heavy, engie, or medic */


DETOUR_SETUP
{
	/* this detour is actually implemented in the shared detour for
	 * CTFPlayer::SpeakConceptIfAllowed */
	
	return true;
}

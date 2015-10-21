#include "all.h"


DETOUR(responses_suppress_giant_sentrybuster);
/* when a sentry buster spawns, disallow the TLK_MVM_GIANT_CALLOUT response */


DETOUR_SETUP
{
	/* this detour is actually implemented in the shared detour for
	 * CTFPlayer::SpeakConceptIfAllowed */
	
	return true;
}

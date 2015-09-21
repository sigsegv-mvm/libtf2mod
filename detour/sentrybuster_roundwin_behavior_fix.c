#include "all.h"


DETOUR(sentrybuster_roundwin_behavior_fix);
/* disallow sentry busters from having their behavior overridden to
 * CTFBotSeekAndDestroy when they win the wave (which causes them to stop
 * attempting to destroy sentries and makes them attempt to caber players) */


static nextbot_event_response_t (*trampoline_CTFBotTacticalMonitor_Update)(CTFBotTacticalMonitor* this, CTFBot*, float);


static nextbot_event_response_t detour_CTFBotTacticalMonitor_Update(CTFBotTacticalMonitor* this, CTFBot* bot, float f1)
{
	//pr_info("CTFBotTacticalMonitor::Update");
	//pr_debug("(bot #%d)\n"
	//	"  g_pGameRules->m_bPlayingMannVsMachine = %s\n"
	//	"  g_pGameRules->m_iRoundState = %d\n"
	//	"  bot->m_nMission = %d\n",
	//	ENTINDEX(bot),
	//	CTFGameRules_IsPVEModeActive(*g_pGameRules) ? "TRUE" : "FALSE",
	//	*prop_CTFGameRules_m_iRoundState(*g_pGameRules),
	//	*prop_CTFBot_m_nMission(bot));
	
	
	if (CTFGameRules_IsPVEModeActive(*g_pGameRules) &&
		*prop_CTFGameRules_m_iRoundState(*g_pGameRules) == ROUNDSTATE_TEAMWIN &&
		*prop_CTFBot_m_nMission(bot) == TFBOT_MISSION_SENTRY_BUSTER) {
		/* don't call the trampoline, just act like we did nothing */
		return (nextbot_event_response_t){
			0,
			NULL,
			NULL,
			0,
		};
	}
	
	
	return trampoline_CTFBotTacticalMonitor_Update(this, bot, f1);
}


DETOUR_SETUP
{
	DETOUR_CREATE(CTFBotTacticalMonitor_Update);
	
	return true;
}

#include "all.h"


DETOUR(debug_nextbot_input);
/*  */


static void (*trampoline_CTFBot_PressFireButton)(CTFBot* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_PressFireButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseFireButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_CTFBot_PressAltFireButton)(CTFBot* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_PressMeleeButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseMeleeButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_CTFBot_PressSpecialFireButton)(CTFBot* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_PressSpecialFireButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseSpecialFireButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_NextBotPlayer_CTFPlayer_PressUseButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseUseButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_NextBotPlayer_CTFPlayer_PressReloadButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseReloadButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_NextBotPlayer_CTFPlayer_PressForwardButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseForwardButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_NextBotPlayer_CTFPlayer_PressBackwardButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseBackwardButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_NextBotPlayer_CTFPlayer_PressLeftButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseLeftButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_NextBotPlayer_CTFPlayer_PressRightButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseRightButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_NextBotPlayer_CTFPlayer_PressJumpButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseJumpButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_NextBotPlayer_CTFPlayer_PressCrouchButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseCrouchButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_NextBotPlayer_CTFPlayer_PressWalkButton)(NextBotPlayer_CTFPlayer* this, float);
static void (*trampoline_NextBotPlayer_CTFPlayer_ReleaseWalkButton)(NextBotPlayer_CTFPlayer* this);

static void (*trampoline_NextBotPlayer_CTFPlayer_SetButtonScale)(NextBotPlayer_CTFPlayer* this, float, float);


static ConVar cvar_entindex;
static ConVar cvar_backtrace;
static ConVar cvar_buttonscale;
static ConVar cvar_mask_attack;
static ConVar cvar_mask_attack2;
static ConVar cvar_mask_attack3;
static ConVar cvar_mask_use;
static ConVar cvar_mask_reload;
static ConVar cvar_mask_forward;
static ConVar cvar_mask_back;
static ConVar cvar_mask_moveleft;
static ConVar cvar_mask_moveright;
static ConVar cvar_mask_jump;
static ConVar cvar_mask_duck;
static ConVar cvar_mask_speed;


static inline __attribute__((always_inline)) void _print_input_info(const char *name, ConVar* cvar, bool release, void *this, float duration)
{
	if (ConVar_GetInt(&cvar_entindex) != 0 && this != NULL &&
		ENTINDEX(this) == ConVar_GetInt(&cvar_entindex) &&
		ConVar_GetInt(cvar) != 0) {
		if (!release) {
			if (duration == -1.0f) {
				cl_con_printf("[%7.3f] +%-9s inf\n", (*gpGlobals)->curtime, name);
			} else {
				cl_con_printf("[%7.3f] +%-9s %5.3f\n", (*gpGlobals)->curtime, name, duration);
			}
		} else {
			cl_con_printf("[%7.3f] -%-9s\n", (*gpGlobals)->curtime, name);
		}
		if (ConVar_GetInt(&cvar_backtrace) != 0) {
			BACKTRACE_CL_CON();
		}
	}
}


static void detour_CTFBot_PressFireButton(CTFBot* this, float duration)
{
	_print_input_info("attack", &cvar_mask_attack, false, this, duration);
	trampoline_CTFBot_PressFireButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_PressFireButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("attack", &cvar_mask_attack, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressFireButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseFireButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("attack", &cvar_mask_attack, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseFireButton(this);
}


static void detour_CTFBot_PressAltFireButton(CTFBot* this, float duration)
{
	_print_input_info("attack2", &cvar_mask_attack2, false, this, duration);
	trampoline_CTFBot_PressAltFireButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_PressMeleeButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("attack2", &cvar_mask_attack2, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressMeleeButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseMeleeButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("attack2", &cvar_mask_attack2, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseMeleeButton(this);
}


static void detour_CTFBot_PressSpecialFireButton(CTFBot* this, float duration)
{
	_print_input_info("attack3", &cvar_mask_attack3, false, this, duration);
	trampoline_CTFBot_PressSpecialFireButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_PressSpecialFireButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("attack3", &cvar_mask_attack3, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressSpecialFireButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseSpecialFireButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("attack3", &cvar_mask_attack3, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseSpecialFireButton(this);
}


static void detour_NextBotPlayer_CTFPlayer_PressUseButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("use", &cvar_mask_use, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressUseButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseUseButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("use", &cvar_mask_use, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseUseButton(this);
}


static void detour_NextBotPlayer_CTFPlayer_PressReloadButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("reload", &cvar_mask_reload, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressReloadButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseReloadButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("reload", &cvar_mask_reload, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseReloadButton(this);
}


static void detour_NextBotPlayer_CTFPlayer_PressForwardButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("forward", &cvar_mask_forward, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressForwardButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseForwardButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("forward", &cvar_mask_forward, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseForwardButton(this);
}


static void detour_NextBotPlayer_CTFPlayer_PressBackwardButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("back", &cvar_mask_back, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressBackwardButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseBackwardButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("back", &cvar_mask_back, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseBackwardButton(this);
}


static void detour_NextBotPlayer_CTFPlayer_PressLeftButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("moveleft", &cvar_mask_moveleft, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressLeftButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseLeftButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("moveleft", &cvar_mask_moveleft, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseLeftButton(this);
}


static void detour_NextBotPlayer_CTFPlayer_PressRightButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("moveright", &cvar_mask_moveright, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressRightButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseRightButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("moveright", &cvar_mask_moveright, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseRightButton(this);
}


static void detour_NextBotPlayer_CTFPlayer_PressJumpButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("jump", &cvar_mask_jump, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressJumpButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseJumpButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("jump", &cvar_mask_jump, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseJumpButton(this);
}


static void detour_NextBotPlayer_CTFPlayer_PressCrouchButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("duck", &cvar_mask_duck, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressCrouchButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseCrouchButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("duck", &cvar_mask_duck, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseCrouchButton(this);
}


static void detour_NextBotPlayer_CTFPlayer_PressWalkButton(NextBotPlayer_CTFPlayer* this, float duration)
{
	_print_input_info("speed", &cvar_mask_speed, false, this, duration);
	trampoline_NextBotPlayer_CTFPlayer_PressWalkButton(this, duration);
}

static void detour_NextBotPlayer_CTFPlayer_ReleaseWalkButton(NextBotPlayer_CTFPlayer* this)
{
	_print_input_info("speed", &cvar_mask_speed, true, this, -1.0f);
	trampoline_NextBotPlayer_CTFPlayer_ReleaseWalkButton(this);
}

static void detour_NextBotPlayer_CTFPlayer_SetButtonScale(NextBotPlayer_CTFPlayer* this, float forward, float side)
{
	if (ConVar_GetInt(&cvar_entindex) != 0 && this != NULL &&
		ENTINDEX(this) == ConVar_GetInt(&cvar_entindex) &&
		ConVar_GetInt(&cvar_buttonscale) != 0) {
		cl_con_printf("[%7.3f] SetButtonScale: fwd %5.3f side %5.3f\n", (*gpGlobals)->curtime, forward, side);
		if (ConVar_GetInt(&cvar_backtrace) != 0) {
			BACKTRACE_CL_CON();
		}
	}
	
	trampoline_NextBotPlayer_CTFPlayer_SetButtonScale(this, forward, side);
}


DETOUR_SETUP
{
	ConVar_ctor(&cvar_entindex,
		"sigsegv_debug_nbinput_entindex", "0", FCVAR_NOTIFY,
		"Debug: NB input: entindex of target bot");
	ConVar_ctor(&cvar_backtrace,
		"sigsegv_debug_nbinput_backtrace", "0", FCVAR_NOTIFY,
		"Debug: NB input: whether to spew stack traces");
	ConVar_ctor(&cvar_buttonscale,
		"sigsegv_debug_nbinput_buttonscale", "1", FCVAR_NOTIFY,
		"Debug: NB input: whether to show calls to SetButtonScale");
	ConVar_ctor(&cvar_mask_attack,
		"sigsegv_debug_nbinput_mask_attack", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +attack");
	ConVar_ctor(&cvar_mask_attack2,
		"sigsegv_debug_nbinput_mask_attack2", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +attack2");
	ConVar_ctor(&cvar_mask_attack3,
		"sigsegv_debug_nbinput_mask_attack3", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +attack3");
	ConVar_ctor(&cvar_mask_use,
		"sigsegv_debug_nbinput_mask_use", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +use");
	ConVar_ctor(&cvar_mask_reload,
		"sigsegv_debug_nbinput_mask_reload", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +reload");
	ConVar_ctor(&cvar_mask_forward,
		"sigsegv_debug_nbinput_mask_forward", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +forward");
	ConVar_ctor(&cvar_mask_back,
		"sigsegv_debug_nbinput_mask_back", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +back");
	ConVar_ctor(&cvar_mask_moveleft,
		"sigsegv_debug_nbinput_mask_moveleft", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +moveleft");
	ConVar_ctor(&cvar_mask_moveright,
		"sigsegv_debug_nbinput_mask_moveright", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +moveright");
	ConVar_ctor(&cvar_mask_jump,
		"sigsegv_debug_nbinput_mask_jump", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +jump");
	ConVar_ctor(&cvar_mask_duck,
		"sigsegv_debug_nbinput_mask_duck", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +duck");
	ConVar_ctor(&cvar_mask_speed,
		"sigsegv_debug_nbinput_mask_speed", "1", FCVAR_NOTIFY,
		"Debug: NB input: mask for +speed");
	
	DETOUR_CREATE(CTFBot_PressFireButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressFireButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseFireButton);
	
	DETOUR_CREATE(CTFBot_PressAltFireButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressMeleeButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseMeleeButton);
	
	DETOUR_CREATE(CTFBot_PressSpecialFireButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressSpecialFireButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseSpecialFireButton);
	
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressUseButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseUseButton);
	
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressReloadButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseReloadButton);
	
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressForwardButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseForwardButton);
	
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressBackwardButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseBackwardButton);
	
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressLeftButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseLeftButton);
	
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressRightButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseRightButton);
	
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressJumpButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseJumpButton);
	
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressCrouchButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseCrouchButton);
	
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_PressWalkButton);
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_ReleaseWalkButton);
	
	DETOUR_CREATE(NextBotPlayer_CTFPlayer_SetButtonScale);
	
	return true;
}

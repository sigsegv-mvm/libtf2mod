#include "all.h"


PATCH(sentrygun_think_every_tick);
/* make sentry guns think on every tick instead of every third tick */


static func_t *func1;


PATCH_INIT
{
	/* CTFObjectSentrygun::SentryThink() */
	func1 = func_register(
		"_ZN16CObjectSentrygun11SentryThinkEv");
}


PATCH_CHECK
{
	size_t check1_base = 0x005a;
	uint8_t check1[] = {
		0xf2, 0x0f, 0x58, 0x05, // +005A  addsd xmm0,DWORD PTR [xxxxxxxx]
	};
	
	
	bool result = true;
	if (!func_verify(func1, check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the addition instruction */
	func_write_nop(func1, 0x005a, 8);
}

#include "all.h"


static bool _entprop_extract_CTFBot_m_hSBTarget_func1(uintptr_t *off)
{
	void *func = CTFBotMissionSuicideBomber_OnStart;
	
	
	size_t check1_base = 0x004f;
	uint8_t check1[] = {
		0x8b, 0x87, ANY_DWORD // +004F  mov eax,DWORD PTR [edi+0x2c00]
		0x83, 0xf8, 0xff,     // +0055  cmp eax,0xffffffff
		0x74, ANY_BYTE        // +0058  je 0x??
	};
	
	size_t runs[][2] = {
		{ 0x004f, 0x0002 },
		{ 0x0055, 0x0004 },
	};
	
	
	if (!entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x0051, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}

uintptr_t entprop_extract_CTFBot_m_hSBTarget(void)
{
	bool fail = false;
	uintptr_t off = 0;
	
	
	uintptr_t off1 = 0;
	_entprop_extract_CTFBot_m_hSBTarget_func1(&off1);
	EXTRACT_CHECK(off1);
	
	
	if (fail) {
		return 0;
	} else {
		return off;
	}
}

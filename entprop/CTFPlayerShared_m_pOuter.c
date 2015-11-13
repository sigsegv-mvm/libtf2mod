#include "all.h"


static bool _entprop_extract_CTFPlayerShared_m_pOuter_func1(uintptr_t *off, void *func)
{
	size_t check1_base = 0x0000;
	uint8_t check1[] = {
		0x55,                 // +0000  push ebp
		0x89, 0xe5,           // +0001  mov ebp,esp
		0x8b, 0x45, 0x08,     // +0003  mov eax,DWORD PTR [ebp+0x8]
		0x8b, 0x80, ANY_DWORD // +0006  mov eax,DWORD PTR [eax+off]
		0x89, 0x45, 0x08,     // +000C  mov DWORD PTR [ebp+0x8],eax
		0x5d,                 // +000F  pop ebp
		0xe9, ANY_DWORD       // +0010  jmp 0x????????
	};
	
	size_t runs[][2] = {
		{ 0x0000, 0x0008 },
		{ 0x000c, 0x0005 },
	};
	
	
	if (!entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x0008, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


static bool _entprop_extract_CTFPlayerShared_m_pOuter_func2(uintptr_t *off)
{
	void *func = CTFPlayerShared_IsAlly;
	
	
	size_t check1_base = 0x0000;
	uint8_t check1[] = {
		0x55,                 // +0000  push ebp
		0x89, 0xe5,           // +0001  mov ebp,esp
		0x53,                 // +0003  push ebx
		0x83, 0xec, ANY_BYTE  // +0004  sub esp,0x??
		0x8b, 0x45, 0x0c,     // +0007  mov eax,DWORD PTR [ebp+0xc]
		0x89, 0x04, 0x24,     // +000A  mov DWORD PTR [esp],eax
		0xe8, ANY_DWORD       // +000D  call 0x????????
		0x89, 0xc3,           // +0012  mov ebx,eax
		0x8b, 0x45, 0x08,     // +0014  mov eax,DWORD PTR [ebp+0x8]
		0x8b, 0x80, ANY_DWORD // +0017  mov eax,DWORD PTR [eax+off]
		0x89, 0x04, 0x24,     // +001D  mov DWORD PTR [esp],eax
		0xe8, ANY_DWORD       // +0020  call 0x????????
	};
	
	size_t runs[][2] = {
		{ 0x0000, 0x0006 },
		{ 0x0007, 0x0007 },
		{ 0x0012, 0x0007 },
		{ 0x001d, 0x0004 },
	};
	
	
	if (!entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x0019, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


static bool _entprop_extract_CTFPlayerShared_m_pOuter_func3(uintptr_t *off)
{
	void *func = CTFPlayerShared_Burn;
	
	
	size_t check1_base = 0x0000;
	uint8_t check1[] = {
		0x55,                 // +0000  push ebp
		0x89, 0xe5,           // +0001  mov ebp,esp
		0x83, 0xec, ANY_BYTE  // +0003  sub esp,0x??
		0x89, 0x5d, 0xf4,     // +0006  mov DWORD PTR [ebp-0xc],ebx
		0x8b, 0x5d, 0x08,     // +0009  mov ebx,DWORD PTR [ebp+0x8]
		0x89, 0x75, 0xf8,     // +000C  mov DWORD PTR [ebp-0x8],esi
		0x8b, 0x75, 0x10,     // +000F  mov esi,DWORD PTR [ebp+0x10]
		0x89, 0x7d, 0xfc,     // +0012  mov DWORD PTR [ebp-0x4],edi
		0x8b, 0x7d, 0x0c,     // +0015  mov edi,DWORD PTR [ebp+0xc]
		0x8b, 0x83, ANY_DWORD // +0018  mov eax,DWORD PTR [ebx+off]
	};
	
	size_t runs[][2] = {
		{ 0x0000, 0x0005 },
		{ 0x0006, 0x0014 },
	};
	
	
	if (!entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x001a, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


static bool _entprop_extract_CTFPlayerShared_m_pOuter_func4(uintptr_t *off)
{
	void *func = CTFPlayerShared_HasDemoShieldEquipped;
	
	
	size_t check1_base = 0x0000;
	uint8_t check1[] = {
		0x55,                 // +0000  push ebp
		0x89, 0xe5,           // +0001  mov ebp,esp
		0x83, 0xec, ANY_BYTE  // +0003  sub esp,0x??
		0x8b, 0x45, 0x08,     // +0006  mov eax,DWORD PTR [ebp+0x8]
		0x8b, 0x80, ANY_DWORD // +0009  mov eax,DWORD PTR [eax+off]
		0x89, 0x04, 0x24,     // +000F  mov DWORD PTR [esp],eax
		0xe8, ANY_DWORD       // +0012  call 0x????????
		0xc9,                 // +0017  leave
		0x85, 0xc0,           // +0018  test eax,eax
		0x0f, 0x95, 0xc0,     // +001A  setne al
		0xc3,                 // +001D  ret
	};
	
	size_t runs[][2] = {
		{ 0x0000, 0x0005 },
		{ 0x0006, 0x0005 },
		{ 0x000f, 0x0004 },
		{ 0x0017, 0x0007 },
	};
	
	
	if (!entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x000b, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


static bool _entprop_extract_CTFPlayerShared_m_pOuter_func5(uintptr_t *off)
{
	void *func = CTFPlayerShared_OnAddBurning;
	
	
	size_t check1_base = 0x0000;
	uint8_t check1[] = {
		0x55,                                           // +0000  push ebp
		0x89, 0xe5,                                     // +0001  mov ebp,esp
		0x83, 0xec, ANY_BYTE                            // +0003  sub esp,0x??
		0x8b, 0x45, 0x08,                               // +0006  mov eax,DWORD PTR [ebp+0x8]
		0xc7, 0x44, 0x24, 0x0c, 0x00, 0x00, 0x00, 0x00, // +0009  mov DWORD PTR [esp+0xc],0x0
		0xc7, 0x44, 0x24, 0x08, 0x00, 0x00, 0x00, 0x00, // +0011  mov DWORD PTR [esp+0x8],0x0
		0xc7, 0x44, 0x24, 0x04, ANY_DWORD               // +0019  mov DWORD PTR [esp+0x4],0x????????
		0x8b, 0x80, ANY_DWORD                           // +0021  mov eax,DWORD PTR [eax+off]
		0x89, 0x04, 0x24,                               // +0027  mov DWORD PTR [esp],eax
		0xe8, ANY_DWORD                                 // +002A  call 0x????????
		0xc9,                                           // +002F  leave
		0xc3,                                           // +0030  ret
	};
	
	size_t runs[][2] = {
		{ 0x0000, 0x0005 },
		{ 0x0006, 0x0017 },
		{ 0x0021, 0x0002 },
		{ 0x0027, 0x0004 },
		{ 0x002f, 0x0002 },
	};
	
	
	if (!entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x0023, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


uintptr_t entprop_extract_CTFPlayerShared_m_pOuter(void)
{
	bool fail = false;
	uintptr_t off = 0;
	
	
	uintptr_t off1a = 0;
	_entprop_extract_CTFPlayerShared_m_pOuter_func1(&off1a,
		CTFPlayerShared_OnAddSpeedBoost);
	EXTRACT_CHECK(off1a);
	
	uintptr_t off1b = 0;
	_entprop_extract_CTFPlayerShared_m_pOuter_func1(&off1b,
		CTFPlayerShared_OnAddDisguisedAsDispenser);
	EXTRACT_CHECK(off1b);
	
	uintptr_t off1c = 0;
	_entprop_extract_CTFPlayerShared_m_pOuter_func1(&off1c,
		CTFPlayerShared_OnRemoveSpeedBoost);
	EXTRACT_CHECK(off1c);
	
	uintptr_t off1d = 0;
	_entprop_extract_CTFPlayerShared_m_pOuter_func1(&off1d,
		CTFPlayerShared_OnRemoveDisguisedAsDispenser);
	EXTRACT_CHECK(off1d);
	
	uintptr_t off1e = 0;
	_entprop_extract_CTFPlayerShared_m_pOuter_func1(&off1e,
		CTFPlayerShared_GetActiveTFWeapon);
	EXTRACT_CHECK(off1e);
	
	uintptr_t off2 = 0;
	_entprop_extract_CTFPlayerShared_m_pOuter_func2(&off2);
	EXTRACT_CHECK(off2);
	
	uintptr_t off3 = 0;
	_entprop_extract_CTFPlayerShared_m_pOuter_func3(&off3);
	EXTRACT_CHECK(off3);
	
	uintptr_t off4 = 0;
	_entprop_extract_CTFPlayerShared_m_pOuter_func4(&off4);
	EXTRACT_CHECK(off4);
	
	uintptr_t off5 = 0;
	_entprop_extract_CTFPlayerShared_m_pOuter_func5(&off5);
	EXTRACT_CHECK(off5);
	
	
	if (fail) {
		return 0;
	} else {
		return off;
	}
}

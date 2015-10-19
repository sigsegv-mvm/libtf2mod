#include "all.h"


#define ANY_BYTE  0x00,
#define ANY_WORD  0x00, 0x00,
#define ANY_DWORD 0x00, 0x00, 0x00, 0x00,

#define NOP_1BYTE 0x00,
#define NOP_3BYTE 0x00, 0x00, 0x00,
#define NOP_7BYTE 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,


static bool _entprop_extract_verify_runs(void *func,
	size_t check_base, uint8_t check[],
	int num_runs, size_t runs[][2])
{
	bool result = true;
	
	for (int i = 0; i < num_runs; ++i) {
		size_t run_off = runs[i][0];
		size_t run_len = runs[i][1];
		
		assert(run_off >= check_base);
		
		if (!func_verify(func,
			run_off, run_len, check + (run_off - check_base))) {
			result = false;
			/* don't break so we don't skip any warnings */
		}
	}
	
	return result;
}


static bool _entprop_extract_ensure_match(const char *caller,
	int num_offs, size_t offs[])
{
	bool mismatch = false;
	for (int i = 1; i < num_offs; ++i) {
		if (offs[i] != offs[i - 1]) {
			mismatch = true;
			break;
		}
	}
	
	if (mismatch) {
		pr_warn("%s: mismatch\n", caller);
		for (int i = 0; i < num_offs; ++i) {
			pr_debug("  %d: %04x\n", i, offs[i]);
		}
	}
	
	return !mismatch;
}


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
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x0008, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
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
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x0019, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
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
		0x89, 0x7d, 0x0c,     // +0015  mov edi,DWORD PTR [ebp+0xc]
		0x8b, 0x83, ANY_DWORD // +0018  mov eax,DWORD PTR [ebx+off]
	};
	
	size_t runs[][2] = {
		{ 0x0000, 0x0005 },
		{ 0x0006, 0x0014 },
	};
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x001a, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
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
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x000b, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
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
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x0023, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


uintptr_t entprop_extract_CTFPlayerShared_m_pOuter(void)
{
	uintptr_t off = 0;
	
	if (_entprop_extract_CTFPlayerShared_m_pOuter_func1(&off,
		CTFPlayerShared_OnAddSpeedBoost)) goto done;
	if (_entprop_extract_CTFPlayerShared_m_pOuter_func1(&off,
		CTFPlayerShared_OnAddDisguisedAsDispenser)) goto done;
	if (_entprop_extract_CTFPlayerShared_m_pOuter_func1(&off,
		CTFPlayerShared_OnRemoveSpeedBoost)) goto done;
	if (_entprop_extract_CTFPlayerShared_m_pOuter_func1(&off,
		CTFPlayerShared_OnRemoveDisguisedAsDispenser)) goto done;
	if (_entprop_extract_CTFPlayerShared_m_pOuter_func1(&off,
		CTFPlayerShared_GetActiveTFWeapon)) goto done;
	if (_entprop_extract_CTFPlayerShared_m_pOuter_func2(&off)) goto done;
	if (_entprop_extract_CTFPlayerShared_m_pOuter_func3(&off)) goto done;
	if (_entprop_extract_CTFPlayerShared_m_pOuter_func4(&off)) goto done;
	if (_entprop_extract_CTFPlayerShared_m_pOuter_func5(&off)) goto done;
	
done:
	return off;
}

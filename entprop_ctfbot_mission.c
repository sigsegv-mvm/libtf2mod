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


static bool _entprop_extract_CTFBot_m_nMission_func1(uintptr_t *off)
{
	void *func = CTFBot_SetMission;
	
	
	size_t check1_base = 0x0000;
	uint8_t check1[] = {
		0x55,                   // +0000  push ebp
		0x89, 0xe5,             // +0001  mov ebp,esp
		0x53,                   // +0003  push ebx
		0x83, 0xec, ANY_BYTE    // +0004  sub esp,0x??
		
		0x8b, 0x5d, 0x08,       // +0007  mov ebx,DWORD PTR [ebp+0x8]
		0x8b, 0x45, 0x0c,       // +000A  mov eax,DWORD PTR [ebp+0xc]
		0x80, 0x7d, 0x10, 0x00, // +000D  cmp BYTE PTR [ebp+0x10],0x0
		0x8b, 0x93, ANY_DWORD   // +0011  mov edx,DWORD PTR [ebx+off]
		
		0x89, 0x83, ANY_DWORD   // +0017  mov DWORD PTR [ebx+off],eax
		
		0x89, 0x93, ANY_DWORD   // +001D  mov DWORD PTR [ebx+off+4],edx
		
#if 0
		0x75, 0x2b,
		0x8c, 0xc0,
		0x73, 0x17,
		0x89, 0x5d, 0x08,
		0x83, 0xc4, ANY_BYTE
		
		0x5b, 0x5d,
		0xe9, CONV_LE(off1)
		
		NOP_3BYTE
		NOP_7BYTE
		
		0x8c, 0xc4, ANY_BYTE
		
		0x5b,
		0x5d,
		0xc3,
		
		NOP_3BYTE
		NOP_7BYTE
		
		0x8b, 0x03,
		0x89, 0x1c, 0x24,
		0xff, 0x90, CONV_LE(off2), // vcall: CTFBot, CTFBot::GetIntentionInterface() const
		0x8b, 0x10,
		0x89, 0x04, 0x24,
		0xff, 0x92, CONV_LE(off3) // vcall: IIntention, IIntention::Reset()
		0xeb, 0xb7,
#endif
	};
	
	size_t runs[][2] = {
		{ 0x0000, 0x0006 },
		{ 0x0007, 0x000c },
		{ 0x0017, 0x0002 },
		{ 0x001d, 0x0002 },
	};
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[3];
	
	func_read(func, 0x0013, sizeof(extracted[0]), &extracted[0]);
	func_read(func, 0x0019, sizeof(extracted[1]), &extracted[1]);
	func_read(func, 0x001f, sizeof(extracted[2]), &extracted[2]);
	
	extracted[2] -= 4;
	
	
	if (!_entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


static bool _entprop_extract_CTFBot_m_nMission_func2(uintptr_t *off)
{
	void *func = CTFBot_IsAllowedToPickUpFlag;
	
	
	size_t check1_base = 0x0070;
	uint8_t check1[] = {
		0x8b, 0x83, ANY_DWORD // +0070  mov eax,DWORD PTR [ebx+off]
		
		0x8b, 0x75, 0xfc,     // +0076  mov esi,DWORD PTR [ebp-0x4]
		0x8b, 0x5d, 0xf8,     // +0079  mov ebx,DWORD PTR [ebp-0x8]
		0x85, 0xc0,           // +007C  test eax,eax
		0x0f, 0x94, 0xc2,     // +007E  sete dl
		0x89, 0xec,           // +0081  mov esp,ebp
		0x89, 0xd0,           // +0083  mov eax,edx
	};
	
	size_t runs[][2] = {
		{ 0x0070, 0x0002 },
		{ 0x0076, 0x000f },
	};
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x0072, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


static bool _entprop_extract_CTFBot_m_nMission_func3(uintptr_t *off)
{
	void *func = CTFBotScenarioMonitor_DesiredScenarioAndClassAction;
	
	
	size_t check1_base = 0x0000;
	uint8_t check1[] = {
		0x55,                 // +0000  push ebp
		0x89, 0xe5,           // +0001  mov ebp,esp
		0x57,                 // +0003  push edi
		0x56,                 // +0004  push esi
		0x53,                 // +0005  push ebx
		0x83, 0xec, ANY_BYTE  // +0006  sub esp,0x??
		
		0x8b, 0x5d, 0x0c,     // +0009  mov ebx,DWORD PTR [ebp+0xc]
		0x8b, 0x83, ANY_DWORD // +000C  mov eax,DWORD PTR [ebx+off]
		
		0x83, 0xf8, 0x02,     // +0012  cmp eax,0x2
		0x0f, 0x84, ANY_DWORD // +0015  je 0x????????
		
		0x83, 0xf8, 0x03,     // +001B  cmp eax,0x3
		0x0f, 0x84, ANY_DWORD // +001E  je 0x????????
	};
	
	size_t runs[][2] = {
		{ 0x0000, 0x0008 },
		{ 0x0009, 0x0005 },
		{ 0x0012, 0x0005 },
		{ 0x001b, 0x0005 },
	};
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x000e, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


static bool _entprop_extract_CTFBot_m_nMission_func4(uintptr_t *off)
{
	void *func = CMissionPopulator_UpdateMission;
	
	
	size_t check1_base = 0x0163;
	uint8_t check1[] = {
		0x8b, 0x4d, 0x0c,     // +0163  mov ecx,DWORD PTR [ebp+0xc]
		0x39, 0x88, ANY_DWORD // +0166  cmp DWORD PTR [eax+off],ecx
		
		0x0f, 0x94, 0xc0,     // +016C  sete al
		0x0f, 0xb6, 0xc0,     // +016F  movzx eax,al
		0x01, 0xc6,           // +0172  add esi,eax
	};
	
	size_t runs[][2] = {
		{ 0x0163, 0x0005 },
		{ 0x016c, 0x0008 },
	};
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x0168, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


static bool _entprop_extract_CTFBot_m_nMission_func5(uintptr_t *off)
{
	void *func = CMissionPopulator_UpdateMissionDestroySentries;
	
	
	size_t check1_base = 0x04c6;
	uint8_t check1[] = {
		0x83, 0xb8, ANY_DWORD 0x02, // +04C6  cmp DWORD PTR [eax+off],0x2
		0x75, ANY_BYTE              // +04CD  jne 0x??
	};
	
	size_t runs[][2] = {
		{ 0x04c6, 0x0002 },
		{ 0x04cc, 0x0002 },
	};
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x04c8, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


static bool _entprop_extract_CTFBot_m_nMission_func6(uintptr_t *off)
{
	void *func = CFuncNavCost_IsApplicableTo;
	
	
	uintptr_t off1 = find_string(
		"server_srv.so", "mission_sentry_buster", true);
	
	uintptr_t off2 = CALC_RELJMP(func, 0x020d,
		CFuncNavCost_HasTag);
	
	uintptr_t off3 = find_string(
		"server_srv.so", "mission_sniper", true);
	
	uintptr_t off4 = CALC_RELJMP(func, 0x0235,
		CFuncNavCost_HasTag);
	
	uintptr_t off5 = find_string(
		"server_srv.so", "mission_spy", true);
	
	uintptr_t off6 = CALC_RELJMP(func, 0x0265,
		CFuncNavCost_HasTag);
	
	
	size_t check1_base = 0x008a;
	uint8_t check1[] = {
		0x8b, 0x86, ANY_DWORD // +008A  mov eax,DWORD PTR [esi+off]
		
		0x83, 0xf8, 0x02,     // +0090  cmp eax,0x2
		0x0f, 0x84, ANY_DWORD // +0093  je 0x????????
		
		0x83, 0xf8, 0x03,     // +0099  cmp eax,0x3
		0x0f, 0x84, ANY_DWORD // +009C  je 0x????????
		
		0x83, 0xf8, 0x04,     // +00A2  cmp eax,0x4
		0x0f, 0x84, ANY_DWORD // +00A5  je 0x????????
		
		0x31, 0xff,           // +00AB  xor edi,edi
		0x83, 0xf8, 0x06,     // +00AD  cmp eax,0x5
		0x0f, 0x84, ANY_DWORD // +00B0  je 0x????????
	};
	
	size_t runs1[][2] = {
		{ 0x008a, 0x0002 },
		{ 0x0090, 0x0005 },
		{ 0x0099, 0x0005 },
		{ 0x00a2, 0x0005 },
		{ 0x00ab, 0x0007 },
	};
	
	size_t check2_base = 0x01f8;
	uint8_t check2[] = {
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off1) // +01F8  mov DWORD PTR [esp+0x4],str_mission_sentry_buster
		0xbf, 0x01, 0x00, 0x00, 0x00,         // +0200  mov edi,0x1
		0x89, 0x1c, 0x24,                     // +0205  mov DWORD PTR [esp],ebx
		0xe8, CONV_LE(off2)                   // +0208  call CFuncNavCost::HasTag
		0x84, 0xc0,                           // +020D  test al,al
		0x0f, 0x85, ANY_DWORD                 // +020F  jne 0x????????
		
		0x8b, 0x86, ANY_DWORD                 // +0215  mov eax,DWORD PTR [esi+off]
		
		0xe9, ANY_DWORD                       // +021B  jmp 0x????????
		
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off3) // +0220  mov DWORD PTR [esp+0x4],str_mission_sniper
		0xbf, 0x01, 0x00, 0x00, 0x00,         // +0228  mov edi,0x1
		0x89, 0x1c, 0x24,                     // +022D  mov DWORD PTR [esp],ebx
		0xe8, CONV_LE(off4)                   // +0230  call CFuncNavCost::HasTag
		0x84, 0xc0,                           // +0235  test al,al
		0x0f, 0x85, ANY_DWORD                 // +0237  jne 0x????????
		
		0x8b, 0x86, ANY_DWORD                 // +023D  mov eax,DWORD PTR [esi+off]
		
		0xe9, ANY_DWORD                       // +0243  jmp 0x????????
		
		NOP_1BYTE
		NOP_7BYTE
		
		0xc7, 0x44, 0x24, 0x04, CONV_LE(off5) // +0250  mov DWORD PTR [esp+0x4],str_mission_spy
		0xbf, 0x01, 0x00, 0x00, 0x00,         // +0258  mov edi,0x1
		0x89, 0x1c, 0x24,                     // +025D  mov DWORD PTR [esp],ebx
		0xe8, CONV_LE(off6)                   // +0260  call CFuncNavCost::HasTag
		0x84, 0xc0,                           // +0265  test al,al
		0x0f, 0x85, ANY_DWORD                 // +0267  jne 0x????????
		
		0x8b, 0x86, ANY_DWORD                 // +026D  mov eax,DWORD PTR [esi+off]
		
		0xe9, ANY_DWORD                       // +0273  jmp 0x????????
	};
	
	size_t runs2[][2] = {
		{ 0x01f8, 0x0019 },
		{ 0x0215, 0x0002 },
		{ 0x021b, 0x0001 },
		{ 0x0220, 0x0019 },
		{ 0x023d, 0x0002 },
		{ 0x0243, 0x0001 },
		{ 0x0250, 0x0019 },
		{ 0x026d, 0x0002 },
		{ 0x0273, 0x0001 },
	};
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs1) / sizeof(*runs1), runs1)) {
		return false;
	}
	if (!_entprop_extract_verify_runs(func, check2_base, check2,
		sizeof(runs2) / sizeof(*runs2), runs2)) {
		return false;
	}
	
	
	uintptr_t extracted[4];
	
	func_read(func, 0x008c, sizeof(extracted[0]), &extracted[0]);
	func_read(func, 0x0217, sizeof(extracted[1]), &extracted[1]);
	func_read(func, 0x023f, sizeof(extracted[2]), &extracted[2]);
	func_read(func, 0x026f, sizeof(extracted[3]), &extracted[3]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


static bool _entprop_extract_CTFBot_m_nMission_func7(uintptr_t *off)
{
	void *func = CTraceFilterObject_ShouldHitEntity;
	
	
	size_t check1_base = 0x0128;
	uint8_t check1[] = {
		0x8b, 0x81, ANY_DWORD // +0128  mov eax,DWORD PTR [ecx+off]
		0x83, 0xf8, 0x02,     // +012E  cmp eax,0x2
		0x74, ANY_BYTE        // +0131  je 0x??
		
		0x83, 0xf8, 0x06,     // +0133  cmp eax,0x6
		0x0f, 0x85, ANY_DWORD // +0136  jne 0x????????
		
		0x31, 0xd2,           // +013C  xor edx,edx
		0xe9, ANY_DWORD       // +013E  jmp 0x????????
	};
	
	size_t runs1[][2] = {
		{ 0x0128, 0x0002 },
		{ 0x012e, 0x0004 },
		{ 0x0133, 0x0005 },
		{ 0x013c, 0x0003 },
	};
	
	size_t check2_base = 0x026d;
	uint8_t check2[] = {
		0x8b, 0x83, ANY_DWORD // +026D  mov eax,DWORD PTR [ebx+off]
		0x83, 0xf8, 0x02,     // +0273  cmp eax,0x2
		0x0f, 0x84, ANY_DWORD // +0276  je 0x????????
		
		0x83, 0xf8, 0x06,     // +027C  cmp eax,0x6
		0x0f, 0x85, ANY_DWORD // +027F  jne 0x????????
		
		0x31, 0xd2,           // +0285  xor edx,edx
		0xe9, ANY_DWORD       // +0287  jmp 0x????????
	};
	
	size_t runs2[][2] = {
		{ 0x026d, 0x0002 },
		{ 0x0273, 0x0005 },
		{ 0x027c, 0x0005 },
		{ 0x0285, 0x0003 },
	};
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs1) / sizeof(*runs1), runs1)) {
		return false;
	}
	if (!_entprop_extract_verify_runs(func, check2_base, check2,
		sizeof(runs2) / sizeof(*runs2), runs2)) {
		return false;
	}
	
	
	uintptr_t extracted[2];
	
	func_read(func, 0x012a, sizeof(extracted[0]), &extracted[0]);
	func_read(func, 0x026f, sizeof(extracted[1]), &extracted[1]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}


uintptr_t entprop_extract_CTFBot_m_nMission(void)
{
	uintptr_t off = 0;
	
	if (_entprop_extract_CTFBot_m_nMission_func1(&off)) goto done;
	if (_entprop_extract_CTFBot_m_nMission_func2(&off)) goto done;
	if (_entprop_extract_CTFBot_m_nMission_func3(&off)) goto done;
	if (_entprop_extract_CTFBot_m_nMission_func4(&off)) goto done;
	if (_entprop_extract_CTFBot_m_nMission_func5(&off)) goto done;
	if (_entprop_extract_CTFBot_m_nMission_func6(&off)) goto done;
	if (_entprop_extract_CTFBot_m_nMission_func7(&off)) goto done;
	
done:
	return off;
}

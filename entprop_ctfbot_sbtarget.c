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
	
	
	if (!_entprop_extract_verify_runs(func, check1_base, check1,
		sizeof(runs) / sizeof(*runs), runs)) {
		return false;
	}
	
	
	uintptr_t extracted[1];
	
	func_read(func, 0x0051, sizeof(extracted[0]), &extracted[0]);
	
	
	if (!_entprop_extract_ensure_match(__func__,
		sizeof(extracted) / sizeof(*extracted), extracted)) {
		return false;
	}
	
	
	*off = extracted[0];
	return true;
}

uintptr_t entprop_extract_CTFBot_m_hSBTarget(void)
{
	uintptr_t off = 0;
	
#ifdef TEST_ENTPROP_EXTRACT
	if (_entprop_extract_CTFBot_m_hSBTarget_func1(&off)) {
		pr_special("%s: PASS #1\n", __func__);
	} else {
		pr_warn("%s: FAIL #1\n", __func__);
	}
#endif
	
	if (_entprop_extract_CTFBot_m_hSBTarget_func1(&off)) goto done;
	
done:
	return off;
}

#include "all.h"


PATCH(deploybomb_suppress_output);
/* suppress hundreds of these lines getting printed when bomb is deployed:
 * "WARNING: MvMDeployBomb::OnContact() RESULT_CRITICAL collision" */


PATCH_CHECK
{
	uintptr_t off1 = (uintptr_t)gpGlobals;
	
	uintptr_t off2 = find_string("server_srv.so",
		"%3.2f: WARNING: %s::%s() RESULT_CRITICAL collision\n", true);
	
	
	size_t check1_base = 0x037b;
	uint8_t check1[] = {
		0xa1, CONV_LE(off1)                 // +037B  mov eax,ds:gpGameRules
		0xf3, 0x0f, 0x10, 0x40, 0x0c,       // +0380  movss xmm0,DWORD PTR [eax+0xc]
		0xc7, 0x04, 0x24, CONV_LE(off2)     // +0385  mov DWORD PTR [esp],str_collision
		0x0f, 0x5a, 0xc0,                   // +038C  cvtps2pd xmm0,xmm0
		0xf2, 0x0f, 0x11, 0x44, 0x24, 0x04, // +038F  movsd QWORD PTR [esp+0x4],xmm0
		0xe8,                               // +0395  call DevMsg(char const*, ...)
		
		/* in the future:
		 * get the addr of DevMsg(char const*, ...) from libtier0_srv.so */
	};
	
	
	bool result = true;
	if (!func_verify(Action_CTFBot_OnContact,
		check1_base, sizeof(check1), check1)) result = false;
	return result;
}


PATCH_APPLY
{
	/* NOP out the DevMsg call */
	func_write_nop(Action_CTFBot_OnContact, 0x0395, 5);
}

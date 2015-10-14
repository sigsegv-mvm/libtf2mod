section .text


extern vcall_CTFWeaponBase_GetWeaponID
extern WeaponID_IsSniperRifle


extern _GLOBAL_OFFSET_TABLE_
get_GOT_esi:
	call .getgot
.getgot:
	pop esi
	add esi,_GLOBAL_OFFSET_TABLE_+$$-.getgot wrt ..gotpc
	ret


; how to call:
; eax: ptr to CTFWeaponBase
; push L_rifle
; push L_other
; call asm_CTFPlayer_OnTakeDamage_Alive_NonRifleEH
; 
; returns:
; depending on whether the weapon is a rifle, this function may return to
;  L_rifle or L_other
global asm_CTFPlayer_OnTakeDamage_Alive_NonRifleEH:function
asm_CTFPlayer_OnTakeDamage_Alive_NonRifleEH:
	push ebp
	mov ebp,esp
	
	push eax
	
	push ebx
	push esi
	call get_GOT_esi
	
	push eax
	xchg ebx,esi
	call vcall_CTFWeaponBase_GetWeaponID wrt ..plt
	xchg ebx,esi
	lea esp,[esp+4]
	
	push eax
	mov eax,[esi+WeaponID_IsSniperRifle wrt ..got]
		call [eax]
	lea esp,[esp+4]
	
	test al,al
	je .ret_other
	
	
	; the weapon is a sniper rifle; return to L_rifle
.ret_rifle:
	pop esi
	pop ebx
	
	pop eax
	
	mov esp,ebp
	pop ebp
	
	
	add esp,8
	ret
	
	
	; the weapon is not a sniper rifle; return to L_rifle
	; also set the caller's [ebp-0xa8] to the CTFWeaponBase ptr
.ret_other:
	pop esi
	pop ebx
	
	pop eax
	
	mov esp,ebp
	pop ebp
	
	mov [ebp-0xa8],eax
	
	add esp,4
	ret 4

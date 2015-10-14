section .text


extern typeinfo_for_CTFWeaponBase
extern typeinfo_for_CWeaponMedigun
extern typeinfo_for_CTFCrossbow
extern __dynamic_cast_NULL_safe


extern _GLOBAL_OFFSET_TABLE_
get_GOT_esi:
	call .getgot
.getgot:
	pop esi
	add esi,_GLOBAL_OFFSET_TABLE_+$$-.getgot wrt ..gotpc
	ret


; how to call:
; eax: ptr to CTFWeaponBase
; push L_medi
; push L_xbow
; push L_fail
; call asm_CTFBotMedicHeal_Update_EnableXbow
; 
; returns:
; ebx: ptr to CTFWeaponBase, possibly casted
; depending on which dynamic cast succeeded, this function may return to
;  L_medi, L_xbow, or L_fail
global asm_CTFBotMedicHeal_Update_EnableXbow:function
asm_CTFBotMedicHeal_Update_EnableXbow:
	mov byte [ebp-0xa8],0
	mov byte [ebp-0xa0],1
	
	push ebp
	mov ebp,esp
	
	push esi
	call get_GOT_esi
	
	; attempt dynamic_cast<CWeaponMedigun>
	mov ebx,eax
	push 0
	mov eax,[esi+typeinfo_for_CWeaponMedigun wrt ..got]
		push dword [eax]
	mov eax,[esi+typeinfo_for_CTFWeaponBase wrt ..got]
		push dword [eax]
	push ebx
	xchg ebx,esi
	call __dynamic_cast_NULL_safe wrt ..plt
	xchg ebx,esi
	lea esp,[esp+16]
	
	test eax,eax
	cmovne ebx,eax
	jne .ret_medi
	
	
	; attempt dynamic_cast<CTFCrossbow>
	push 0
	mov eax,[esi+typeinfo_for_CTFCrossbow wrt ..got]
		push dword [eax]
	mov eax,[esi+typeinfo_for_CTFWeaponBase wrt ..got]
		push dword [eax]
	push ebx
	xchg ebx,esi
	call __dynamic_cast_NULL_safe wrt ..plt
	xchg ebx,esi
	lea esp,[esp+16]
	
	test eax,eax
	mov ebx,eax
	jne .ret_xbow
	
	
	; both dynamic casts failed; return to L_fail
.ret_fail:
	mov esp,ebp
	pop ebp
	
	pop esi
	
	add esp,4
	ret 8
	
	
	; the CTFCrossbow dynamic cast worked; return to L_xbow
.ret_xbow:
	mov esp,ebp
	pop ebp
	
	pop esi
	
	add esp,8
	ret 4
	
	
	; the CWeaponMedigun dynamic cast worked; return to L_medi
.ret_medi:
	mov esp,ebp
	pop ebp
	
	pop esi
	
	add esp,12
	ret

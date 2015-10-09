section .text


extern typeinfo_for_CTFWeaponBase
extern typeinfo_for_CWeaponMedigun
extern __dynamic_cast_NULL_safe


extern _GLOBAL_OFFSET_TABLE_
get_GOT_esi:
	call .getgot
.getgot:
	pop esi
	add esi,_GLOBAL_OFFSET_TABLE_+$$-.getgot wrt ..gotpc
	ret


; how to call:
; ebx: ptr to CTFWeaponBase
; eax: vtable offset for CWeaponMedigun::GetTargetRange
; call asm_CTFBotMedicHeal_Update_GetTargetRange
; 
; returns:
; st(0): the target range, or possibly zero
global asm_CTFBotMedicHeal_Update_GetTargetRange:function
asm_CTFBotMedicHeal_Update_GetTargetRange:
	push ebp
	mov ebp,esp
	
	push esi
	call get_GOT_esi
	
	push eax
	
	push 0
	mov eax,[esi+typeinfo_for_CWeaponMedigun wrt ..got]
		push dword [eax]
	mov eax,[esi+typeinfo_for_CTFWeaponBase wrt ..got]
		push dword [eax]
	push ebx
	call [esi+__dynamic_cast_NULL_safe wrt ..got]
	lea esp,[esp+16]
	
	test eax,eax
	je .not_medi
	
	
	; the dynamic cast succeeded; call CWeaponMedigun::GetTargetRange
.is_medi:
	mov ebx,eax
	pop eax
	
	push ebx
	mov edx,[ebx]
	call [edx+eax]
	lea esp,[esp+4]
	
	jmp .done
	
	
	; the dynamic cast failed; return 0.0f
.not_medi:
	pop eax
	
	fldz
	
	
.done:
	mov esp,ebp
	pop ebp
	
	pop esi
	
	mov edx,[ebp+0x10]
	mov ecx,edi
	
	ret

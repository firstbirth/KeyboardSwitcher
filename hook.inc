InstallHook		proto 	:DWORD
UninstallHook	proto	:DWORD
KeyboardHookProc	proto :DWORD,:DWORD,:DWORD

.code
InstallHook proc hInst:DWORD
	invoke SetWindowsHookEx, WH_KEYBOARD_LL, offset KeyboardHookProc,hInst,0
	ret
InstallHook EndP
;==================================================
UninstallHook proc hHook1:DWORD
	invoke UnhookWindowsHookEx, hHook1
	ret
UninstallHook EndP
;==================================================
KeyboardHookProc proc nCode:DWORD, wParam:DWORD, lParam:DWORD
	invoke CallNextHookEx,hHook,nCode,wParam,lParam
	;-----------------------------------------------------
	push nCode
	pop eax
	;-----------------------------------------------------
	or eax,eax
	jl @@Ret
	;-----------------------------------------------------
	push wParam
	pop eax
	;-----------------------------------------------------
	cmp eax, WM_KEYDOWN
	jne @@Ret
	;-----------------------------------------------------
	push lParam
	pop eax
	;-----------------------------------------------------
	cmp dword ptr[eax], VK_CAPITAL
	jne @@Ret
	;-----------------------------------------------------
    invoke KeyboardSwitcher
    xor eax,eax
    inc eax ;<-setting returning value to 1 for avoid system handler
    ret
    
@@Ret:
	xor eax,eax
    ret
KeyboardHookProc ENDP
;==================================================
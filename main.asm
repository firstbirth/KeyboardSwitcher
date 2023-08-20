include main.inc
;===============

.code
start:
	fnx hInstance = GetModuleHandle,0
	;--------------------------------
	fn DialogBoxParam,eax,IDD_DLG,0,offset DialogProc,0
	;--------------------------------
	fn ExitProcess,eax
	
;=======================================================

DialogProc proc uses ebx esi edi hWin:DWORD,uMsg:DWORD, wParam:DWORD, lParam:DWORD
	.if uMsg == WM_INITDIALOG
		;-------------------------
		fn InstallHook, hInstance
		mov hHook, eax
		;-------------------------
		fn on_init, hWin, hInstance
		
	.elseif uMsg == WM_CLOSE
	
		jmp @@Add
	
	.elseif uMsg == WM_DESTROY
		;-----------------------
		fn on_destroy
		;-----------------------
		fn UninstallHook, hHook
		
	.elseif uMsg == WM_COMMAND
	
		.if	wParam == IDC_BTN_TRAY
		
			fn SendMessage,hWin,WM_SIZE, SIZE_MINIMIZED,0
		
		.elseif wParam == IDC_BTN_EXIT
			
			fn on_destroy
		
		.endif
		
	.elseif uMsg == WM_SIZE
	
		.if wParam == SIZE_MINIMIZED
@@Add:
			fn notify_add_icon, hWin,IDI_APP,hInstance, offset szTitle
			;------------------
			xor eax,eax
			inc eax
			jmp @@Ret
			
		.endif
		
	.else
	
		fn notify_def_proc, uMsg,wParam,lParam
		
	.endif
	
	xor eax,eax
	
@@Ret:
	ret
DialogProc endp	
;===============================================
end start
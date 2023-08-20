WM_USER_SHELLICON 		=		WM_USER + 1

notify_add_icon  proto :DWORD,:DWORD,:DWORD,:DWORD
notify_delete    proto
notify_def_proc  proto :DWORD,:DWORD,:DWORD
notify_destroy   proto
notify_init_menu proto :DWORD,:DWORD

.data?
nid		NOTIFYICONDATA	<>
hPopupMenu	dd		?

.code
notify_add_icon proc uses ebx esi edi hWin:DWORD,id:DWORD,hInst:DWORD,lpszTip:DWORD

	push nid.hIcon
	pop eax
	or eax, eax
	jne @F
	;--------------
	mov nid.cbSize, sizeof nid
	;--------------
	push hWin
	pop nid.hwnd
	mov nid.uID,1
	;--------------
	mov nid.uFlags, NIF_ICON or NIF_MESSAGE or NIF_TIP
	mov nid.uCallbackMessage, WM_USER_SHELLICON
	;--------------
	fn LoadIcon, hInst, id
	;--------------
	push eax
	pop nid.hIcon
	;--------------
	push lpszTip
	push offset nid.szTip
	;--------------
	call lstrcpy
	;--------------
@@:
	fn ShowWindow,hWin,SW_HIDE
	;-------------------------
	fn Shell_NotifyIcon, NIM_ADD, offset nid
		
	ret
notify_add_icon endp
;============================================
notify_delete proc uses ebx esi edi

	push nid.hwnd
	pop ebx
	;------------
	fn Shell_NotifyIcon,NIM_DELETE, offset nid
	;------------
	fn ShowWindow, ebx, SW_SHOWNORMAL
	;------------
	fn SetForegroundWindow,ebx
	ret
notify_delete endp
;============================================
notify_def_proc proc uses ebx esi edi uMsg:DWORD,wParam:DWORD,lParam:DWORD

	cmp uMsg, WM_USER_SHELLICON
	jne @@Ret
	;--------------------------
	push wParam
	push nid.uID
	pop eax
	pop edx
	;--------------------------
	cmp eax, edx
	jne @@Ret
	;--------------------------
	cmp lParam, WM_LBUTTONDBLCLK
	jne @F
	;---------------------------
	call notify_delete
	;---------------------------
	jmp @@Ret
@@:
	cmp lParam, WM_RBUTTONDOWN
	jne @@Ret
	;---------------------------
	call notify_track_menu
	
@@Ret:
	ret
notify_def_proc endp
;==============================================
notify_track_menu proc
	LOCAL mouse_pos:POINT
	LOCAL selection:DWORD
	
	fn GetCursorPos, addr mouse_pos
	;-----------------------------
	fn SetForegroundWindow, nid.hwnd
	;-----------------------------
	fnx selection = TrackPopupMenu, hPopupMenu, TPM_RIGHTALIGN or TPM_RIGHTBUTTON or TPM_RETURNCMD,\
									mouse_pos.x, mouse_pos.y,0,nid.hwnd,0
	;------------------------------
	;Process the selected menu item
	;------------------------------
	
	push selection
	pop eax
	;------------------------------
	.if eax == IDM_OPEN
		
		call notify_delete
		
	.elseif eax == IDM_EXIT
	
		fn Shell_NotifyIcon, NIM_DELETE, offset nid
		;-----------------------------------------
		fn DestroyWindow,nid.hwnd
				
	.endif
	ret
notify_track_menu endp
;=================================================
notify_destroy proc uses ebx esi edi

	push nid.hIcon
	pop eax
	or eax,eax
	je @F
	;---------------
	fn DeleteObject,eax
	;---------------
	jmp @@Ret
	;---------------
	
@@:
	push hPopupMenu
	pop eax
	or eax,eax
	je @@Ret
	;---------------
	fn DestroyMenu,eax
	
@@Ret:
	ret
notify_destroy endp
;==============================================
notify_init_menu proc uses ebx esi edi menu_data:DWORD,start_id:DWORD
	
	fn CreatePopupMenu;
	;------------------
	push eax
	pop hPopupMenu
	;------------------
	push start_id
	push menu_data
	pop esi
	pop edi
	;------------------
	xor ebx,ebx
	
@@For:
	mov eax, dword ptr[esi+ebx*4]
	or eax,eax
	je @@Ret
	;----------------------------
	fn AppendMenu, hPopupMenu, MF_STRING,edi,eax
	;----------------------------
	inc edi
	inc ebx
	jmp @@For
	
@@Ret:

	ret
notify_init_menu endp
;================================================
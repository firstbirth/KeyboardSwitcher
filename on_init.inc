on_init		proto 		:DWORD, :DWORD

.code
on_init proc hWin:DWORD,hInst:DWORD

	fn LoadIcon, hInst, IDI_APP
	;--------------------------
	fn SendMessage, hWin, WM_SETICON, 1, eax
	;--------------------------
	fn notify_init_menu, offset Popupmenu, IDM_OPEN
	
	ret
on_init endp
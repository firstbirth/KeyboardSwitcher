include \masm32\include\masm32rt.inc
;===================================

DialogProc	proto	:DWORD,:DWORD,:DWORD,:DWORD

IDD_DLG			=		1001
IDI_APP			=		100
IDM_OPEN		=		1
IDM_EXIT		=		2
;------------------------------------------------
IDC_BTN_TRAY 	=		1003
IDC_BTN_EXIT 	= 		1004
;------------------------------------------------
.data?
hInstance 	dd		?
hHook		dd		?

.data
szTitle		db		"Keyboard Switcher",0
;----------------------------------------
szOpen		db		"Open",0
szExit		db		"Exit",0
;----------------------------------------
Popupmenu 	dd	offset szOpen
			dd	offset szExit
;----------------------------------------
include notifyicon32.inc
include on_close.inc
include on_destroy.inc
include on_init.inc
include keyboardswitcher.inc
include hook.inc

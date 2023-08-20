KeyboardSwitcher proto

.data
szENGLANG = 4090409h
szRUSLANG = 4190419h

.code
KeyboardSwitcher proc 
	fn GetKeyboardLayout,0
	;---------------------
	cmp eax, szENGLANG
	je @@SwitchToRus
	;---------------------
	invoke SendMessage,HWND_BROADCAST,WM_INPUTLANGCHANGEREQUEST,0, szENGLANG
	jmp @@Ret
	;---------------------
@@SwitchToRus:
	invoke SendMessage,HWND_BROADCAST,WM_INPUTLANGCHANGEREQUEST,0, szRUSLANG
	jmp @@Ret
	
@@Ret:
	Ret
KeyboardSwitcher EndP
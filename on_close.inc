on_close		proto		:DWORD

.code
on_close proc hWin:DWORD
	
	fn notify_destroy
	;----------------
	fn EndDialog,hWin,0
	ret
on_close endp
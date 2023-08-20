on_destroy		proto

.code
on_destroy proc
	
	fn notify_destroy
	;----------------
	fn PostQuitMessage,0
	;----------------
	ret
on_destroy endp
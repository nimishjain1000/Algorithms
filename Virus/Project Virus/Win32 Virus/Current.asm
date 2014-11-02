.386
.model flat,stdcall
option casemap:none

   include windows.inc
   include user32.inc
   include kernel32.inc
   include masm32.inc
   include masm32rt.inc
   include msvcrt.inc
   
   includelib user32.lib
   includelib kernel32.lib
   includelib masm32.lib
   includelib msvcrt.lib
   
.data
FolderPath                      BYTE                        "C:\Documents and Settings\F.U.C.K\Desktop\*.exe", 0
FindFirstFileError              BYTE                        "FindFirstFile failed ", 0
FindFirstFileSuccess            BYTE                        "First file found with success ", 0
FindNextFileError               BYTE                        "FindNextFile failed ", 0
FindNextFileSuccess             BYTE                        "FirstNextFile found with success ", 0
PrintStructAddr                 BYTE                        "addr=Ox%08X", 0
PrintFileName                   BYTE                        "%s", 0

fileFilter  db "*.*",0
backDir db "..",0
path db "C:\Documents and Settings\F.U.C.K\Desktop\",0
exeFilter db "*.exe",0
count db 0
.data?
hDir db 256 dup (?)
hFile                           HANDLE 			      ?
findFileData                    WIN32_FIND_DATA   		<>   ; file handle data
retFindNextFile                 BOOL                        ?
ErrorCode                       DWORD                       ?

.code
; ---------------------------------------------------------------------------
virusCode:
	call oldVirus
	invoke ExitProcess,0
		
oldVirus proc
findFirst:	
	invoke FindFirstFile, addr FolderPath, addr findFileData
	.if eax==INVALID_HANDLE_VALUE
		invoke GetLastError
		mov ErrorCode,eax
		invoke MessageBox,NULL,addr FindFirstFileError,addr ErrorCode,MB_ICONERROR
		invoke ExitProcess,0
	.else
		mov hFile, eax
		mov ebx, OFFSET findFileData   ; Move file handle to bx
		invoke MessageBox,NULL,addr [ebx].WIN32_FIND_DATA.cFileName,addr FindFirstFileSuccess,MB_OK
	.endif
findNext:	
	invoke FindNextFile, addr hFile , addr findFileData
	.if eax==INVALID_HANDLE_VALUE
		invoke GetLastError
		mov ErrorCode,eax
		invoke MessageBox,NULL,addr FindNextFileError,addr ErrorCode,MB_ICONERROR
		invoke ExitProcess,0
	.else
		mov hFile, eax
		mov ebx, OFFSET findFileData   ; Move file handle to bx
		invoke MessageBox,NULL,addr [ebx].WIN32_FIND_DATA.cFileName,addr FindNextFileSuccess,MB_OK
		jmp findNext
	.endif
exit: 
	invoke ExitProcess,0
	ret
oldVirus endp


ScanFiles proc
	; Declare local varibles
	LOCAL fileFD : WIN32_FIND_DATA    ; ref 
	LOCAL fileHD : dword
	
	; Find first file 
	; @param path (all : *.*)
	; @param ptr to WIN32_FIND_DATA(fileFD)
	; return : 
	;  + Success :
	;  + Fail : 
	invoke FindFirstFile,addr fileFilter, addr fileFD
		; check return value of eax
		.if eax!= INVALID_HANDLE_VALUE
			; get extend error information
			invoke GetLastError
			; put file 
			mov fileHD,eax
			.while eax > 0 
					lea esi,fileFD.cFileName
					cmp [esi],byte ptr "."
					je nextfile
					; check if result is dir
					.if fileFD.dwFileAttributes == 16
						invoke SetCurrentDirectory,addr fileFD.cFileName
						invoke GetCurrentDirectory,2048,addr hDir
						call ScanFilesInSelectFolder
						call ScanFiles
						invoke SetCurrentDirectory, addr backDir
					.else
						; else check if file extension is exe
						; call infect file			
					.endif
			nextfile:
					invoke FindNextFile, fileHD, addr fileFD
			.endw
			invoke FindClose,fileHD
		.endif
	ret
ScanFiles endp

ScanFilesInSelectFolder proc
	LOCAL fileFD : WIN32_FIND_DATA    ; ref 
	LOCAL fileHD : dword
	
	invoke FindFirstFile,addr exeFilter, addr fileFD
	.if eax!=INVALID_HANDLE_VALUE
			mov fileHD,eax
			.while eax > 0
				; get current dir from search above
				invoke GetCurrentDirectory,2048,addr hDir
				print " Found :"
				print addr hDir
				print "\"
				invoke StdOut,addr fileFD.cFileName
				print " ",13,10
				inc count
				.if count==25
						invoke ExitProcess,0
						mov count,0
				.endif
				invoke FindNextFile,fileHD,addr fileFD
			.endw
			invoke FindClose,fileHD
	.endif
	ret
ScanFilesInSelectFolder endp

end virusCode

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
FolderPath                      BYTE                        "C:\Users\F.U.C.K\Desktop\*.exe", 0
FindFirstFileError              BYTE                        "FindFirstFile failed ", 0
FindFirstFileSuccess            BYTE                        "First file found with success ", 0
FindNextFileError               BYTE                        "FindNextFile failed ", 0
FindNextFileSuccess            BYTE                         "FirstNextFile found with success ", 0
PrintStructAddr                 BYTE                        "addr=Ox%08X", 0
PrintFileName                   BYTE                        "%s", 0
.data?

hFile                           HANDLE 			      ?
findFileData                    WIN32_FIND_DATA   		<>   ; file handle data
retFindNextFile                 BOOL                        ?
ErrorCode                       DWORD                       ?

.code
; ---------------------------------------------------------------------------
	
virusStart:
findFirst:	
	invoke FindFirstFile, addr FolderPath, addr findFileData
	.if eax==INVALID_HANDLE_VALUE
		invoke GetLastError
		mov ErrorCode,eax
		invoke MessageBox,NULL,addr FindFirstFileError,addr ErrorCode,MB_ICONERROR
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
		invoke MessageBox,NULL,addr FindFirstFileError,addr ErrorCode,MB_ICONERROR
	.else
		mov hFile, eax
		mov ebx, OFFSET findFileData   ; Move file handle to bx
		invoke MessageBox,NULL,addr [ebx].WIN32_FIND_DATA.cFileName,addr FindNextFileSuccess,MB_OK
	.endif
exit: 
		invoke ExitProcess,0
end virusStart

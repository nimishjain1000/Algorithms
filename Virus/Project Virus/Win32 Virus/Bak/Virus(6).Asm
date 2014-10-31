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
PrintStructAddr                 BYTE                        "addr=Ox%08X", 0

.data?

hFile                           HANDLE 						?
findFileData                    WIN32_FILE_ATTRIBUTE_DATA   <>
retFindNextFile                 BOOL                        ?
ErrorCode                       DWORD                       ?

.code
; ---------------------------------------------------------------------------
	
virusStart:
	
	invoke FindFirstFile, addr FolderPath, addr findFileData
		.if eax==INVALID_HANDLE_VALUE
			invoke GetLastError
			mov ErrorCode,eax
			invoke MessageBox,NULL,addr FindFirstFileError,addr ErrorCode,MB_ICONERROR
		.endif
	mov ebx, OFFSET findFileData
	lea eax, [ebx].WIN32_FIND_DATA.cFileName
	invoke crt_printf,  addr PrintFileName, offset findFileData.cFileName
	invoke ExitProcess,0
	
end virusStart

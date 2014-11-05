.586
.model flat,stdcall
option casemap:none

   include windows.inc
   include user32.inc
   include kernel32.inc
   include masm32.inc
   include masm32rt.inc
   
   
   includelib user32.lib
   includelib kernel32.lib
   includelib masm32.lib
   
.data
FindFirstFileError              BYTE                        "FindFirstFile failed ", 0
FindFirstFileSuccess            BYTE                        "First file found with success ", 0
FindNextFileError               BYTE                        "FindNextFile failed ", 0
FindNextFileSuccess             BYTE                        "FirstNextFile found with success ", 0
FolderFound           		    BYTE                        "Folder found", 0

fileFilter 						db 							"*.*",0
backDir 						db 							"..",0
path 							BYTE 							"C:\Documents and Settings\F.U.C.K\Desktop\virus\",0
pathTest						BYTE							"C:\Documents and Settings\F.U.C.K\Desktop\virus\test\",0
exeFilter 						db 							"*.exe",0
count 							db 							0

.data?
hDir 							db 							256 dup (?)
ErrorCode                       DWORD                       ?

.code
; ---------------------------------------------------------------------------
virusCode:
	invoke SetCurrentDirectory, addr path
	call ScanFiles
	;call ScanFilesInSelectFolder
	invoke ExitProcess,0
		
ScanFiles proc
	; Declare local varibles
	LOCAL fileFD  : WIN32_FIND_DATA     
	LOCAL fileHD  : HANDLE
	LOCAL subPath : BYTE
	; Find first file 
	; @param path (all : *.*)
	; @param ptr to WIN32_FIND_DATA(fileFD)
	; return : 
	;  + Success :
	;  + Fail : 
	invoke FindFirstFile,addr exeFilter, addr fileFD
		; check return value of eax
		.if eax!=INVALID_HANDLE_VALUE
			mov fileHD,eax
			invoke MessageBox,NULL,addr fileFD.cFileName,addr FindFirstFileSuccess,MB_OK
			invoke GetLastError
			mov ErrorCode,eax
			.while ErrorCode==0
				;lea esi,fileFD.cFileName
				;cmp [esi],byte ptr "."
				;je nextfile
				; check if result is dir
				.if (fileFD.dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY)
				;.if (fileFD.dwFileAttributes==16)
					invoke MessageBox,NULL,addr fileFD.cFileName,addr FolderFound,MB_OK
					;invoke SetCurrentDirectory,addr pathTest
					;invoke GetCurrentDirectory,1024,addr hDir
					;call ScanFilesInSelectFolder
					;invoke SetCurrentDirectory, addr backDir 
				.else
					invoke MessageBox,NULL,addr fileFD.cFileName,addr FindNextFileSuccess,MB_OK
				.endif
			nextfile:
				invoke FindNextFile, fileHD, addr fileFD
					invoke GetLastError
					mov ErrorCode,eax
			.endw	
		invoke FindClose,fileHD
		.endif
	ret
ScanFiles endp

ScanFilesInSelectFolder proc
	LOCAL fileFD : WIN32_FIND_DATA    ; ref 
	LOCAL fileHD : DWORD
	
	invoke FindFirstFile,addr exeFilter, addr fileFD
		.if eax!=INVALID_HANDLE_VALUE
			mov fileHD,eax
			invoke MessageBox,NULL,addr fileFD.cFileName,addr FindFirstFileSuccess,MB_OK
			invoke GetLastError
				mov ErrorCode,eax
				.if ErrorCode==0
					.while ErrorCode==0 ;.repeat
						invoke FindNextFile,fileHD,addr fileFD
						invoke GetLastError
						mov ErrorCode,eax
						invoke MessageBox,NULL,addr fileFD.cFileName,addr FindNextFileSuccess,MB_OK
					.endw;.until ErrorCode!=0
				.endif
		.endif
		invoke FindClose,fileHD
	ret
ScanFilesInSelectFolder endp

CheckFile proc fileName:dword
	lea esi,fileName
	
	ret

CheckFile endp

end virusCode

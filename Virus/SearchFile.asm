.model  small

.code

ORG     100H   
 
START:    
    
search_first:
  mov ah,4eh  
  mov dx,offset COM_FILE
  xor cx,cx
search_loop:    
  int 21h
  jc failed
  mov ah,09h
  mov dx,9eh
  int 21h     
  mov ah,4fh
  jc search_loop 

failed: ret    
         
COM_FILE        DB      '*.COM',0       ;string for COM file search

END     START 
     

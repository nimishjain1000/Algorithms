mov cx,5                      ; set 5 bytes ghi vo host
    lea dx,[di+OFFSET TEST_JMP]      ; tai vi tri data_array
    mov ah,40H
    int 21H 

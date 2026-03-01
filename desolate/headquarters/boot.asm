; 我需要一个16位的引导程序
; 我需要一个包含安全32位的读写跳转

[bits 16]
[org 0x7c00]

start:
    ; 先读内核到 0x1000（BIOS 调用）
    mov ax, 0
    mov es, ax
    mov bx, 0x1000
    mov ah, 0x02
    mov al, 1
    mov ch, 0
    mov cl, 2
    mov dh, 0
    int 0x13
    jc disk_error

    cli
    lgdt [gdt_desc]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:pm_entry

[bits 32]
pm_entry:
    ; 设置数据段寄存器
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x7c00        ; 栈指针可以沿用实模式的设置

    ; 清空页目录所在内存（4KB）
    mov edi, 0x2000
    mov ecx, 1024          ; 1024 个 dword
    xor eax, eax
    rep stosd

    ; 设置页目录的第一项：指向页表 0x3000，属性存在+可写+用户（0x003）
    mov dword [0x2000], 0x3003   ; 页表地址 0x3000，属性 0x3（存在+可写）

    ; 清空页表所在内存（4KB）
    mov edi, 0x3000
    mov ecx, 1024
    xor eax, eax
    rep stosd

    ; 设置页表的 1024 项，映射物理地址 0x0000 ~ 0x3FFFFF（4MB）
    mov ebx, 0x3000        ; 页表起始地址
    mov eax, 0x00000003    ; 物理地址从 0 开始，属性存在+可写
    mov ecx, 1024
fill_pt:
    mov [ebx], eax
    add ebx, 4
    add eax, 0x1000        ; 下一物理页 4KB
    loop fill_pt

    ; 加载页目录地址到 CR3
    mov eax, 0x2000
    mov cr3, eax

    ; 开启分页
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    ; 现在可以跳转到内核（假设内核在 0x1000）
    jmp 0x08:0x1000

disk_error:
    cli
    hlt

gdt_start:
    dq 0
gdt_code:
    dw 0xffff
    dw 0
    db 0
    db 0x9a
    db 0xcf
    db 0
gdt_data:
    dw 0xffff
    dw 0
    db 0
    db 0x92
    db 0xcf
    db 0
gdt_end:

gdt_desc:
    dw gdt_end - gdt_start - 1
    dd gdt_start

times 510 - ($-$$) db 0
dw 0xaa55
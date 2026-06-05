/* ==========================================
 * 声明区域 (面向契约设计)
 * ========================================== */
#define VGA_BUFFER 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define IDT_SIZE 256  /* 定义中断描述符表的大小 */

/* 多重启动头，QEMU识别的钥匙 */
#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_HEADER_FLAGS 0x00000003
#define MULTIBOOT_HEADER_CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

__attribute__((section(".multiboot"))) 
struct {
    unsigned int magic;
    unsigned int flags;
    unsigned int checksum;
} multiboot_header = {
    MULTIBOOT_HEADER_MAGIC,
    MULTIBOOT_HEADER_FLAGS,
    MULTIBOOT_HEADER_CHECKSUM
};

/* 定义中断描述符表项的结构 */
struct idt_entry {
    unsigned short base_low;
    unsigned short selector;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed));

/* 定义中断描述符表指针的结构 */
struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[IDT_SIZE];
struct idt_ptr idt_p;

/* ==========================================
 * 计算区域 (纯函数核心)
 * ========================================== */
void vga_putchar(char c, int x, int y) {
    volatile unsigned char *vga = (volatile unsigned char *)VGA_BUFFER;
    int offset = (y * VGA_WIDTH + x) * 2;
    vga[offset] = c;
    vga[offset + 1] = 0x07;
}

void vga_print(const char *str, int x, int y) {
    while (*str) {
        vga_putchar(*str++, x++, y);
        if (x >= VGA_WIDTH) {
            x = 0;
            y++;
        }
    }
}

void vga_clear(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_putchar(' ', x, y);
        }
    }
}

void idt_set_gate(unsigned char num, unsigned int base, unsigned short selector, unsigned char flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector = selector;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

/* ==========================================
 * 管道区域 (反应式架构)
 * ========================================== */
void isr_handler(void) {
    vga_print("Interrupt Received!", 0, 1);
    
    /* 发送中断结束信号(EOI)给主8259 PIC，告诉它中断处理完毕 */
    __asm__ __volatile__ ("movb $0x20, %al\n\toutb %al, $0x20");
}

/* 所有的中断处理函数都会跳转到这里 */
__asm__ (
    ".globl isr_common_stub\n"
    "isr_common_stub:\n"
    "    pusha\n"
    "    call isr_handler\n"
    "    popa\n"
    "    iret\n"
);

extern void isr_common_stub(void);

/* 初始化中断描述符表 */
void idt_init(void) {
    idt_p.limit = sizeof(struct idt_entry) * IDT_SIZE - 1;
    idt_p.base = (unsigned int)&idt;

    /* 暂时将所有中断指向同一个处理函数，用于验证 */
    for (int i = 0; i < IDT_SIZE; i++) {
        idt_set_gate(i, (unsigned int)isr_common_stub, 0x08, 0x8E);
    }

    /* 加载中断描述符表 */
    __asm__ __volatile__ ("lidt %0" :: "m"(idt_p));
    
    /* 初始化8259 PIC，重新映射IRQ，之后开启键盘中断等 */
    __asm__ __volatile__ (
        "movb $0x11, %al\n\toutb %al, $0x20\n\t"
        "movb $0x11, %al\n\toutb %al, $0xA0\n\t"
        "movb $0x20, %al\n\toutb %al, $0x21\n\t"
        "movb $0x28, %al\n\toutb %al, $0xA1\n\t"
        "movb $0x04, %al\n\toutb %al, $0x21\n\t"
        "movb $0x02, %al\n\toutb %al, $0xA1\n\t"
        "movb $0x01, %al\n\toutb %al, $0x21\n\t"
        "movb $0x01, %al\n\toutb %al, $0xA1\n\t"
        "movb $0xFC, %al\n\toutb %al, $0x21\n\t"
        "movb $0xFF, %al\n\toutb %al, $0xA1"
    );
}

void kernel_main(void) {
    vga_clear();
    vga_print("Kernel Started...", 0, 0);

    idt_init();
    vga_print("IDT Initialized.", 0, 1);
    
    /* 开启中断 */
    __asm__ __volatile__ ("sti");

    /* 规则模型启动后，进入无限循环 */
    for (;;) {
        __asm__ __volatile__ ("hlt");
    }
}
ENTRY(kernel_main)

SECTIONS {
    . = 1M;

    .multiboot : {
        *(.multiboot)  /* 多重启动头必须放在最前面 */
    }

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}

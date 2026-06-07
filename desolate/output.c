// 我们需要 NULL，它定义在 <stddef.h>，或者我们可以自己定义
#define NULL ((void*)0)
// 我们需要一个布尔类型来标记状态
#define TRUE 1
#define FALSE 0

// 我们输出函数的契约：接受一个字符和一个上下文，决定如何输出
// 这样就能把输出逻辑抽象成可替换的代码块。
typedef int (*output_func)(char c, void *context);

typedef int (*format_handler)(void **args, output_func output, void *context, int *written);

typedef struct {
    char spec;
    format_handler handler;
} format_map;

// 这是一个最小的 Linux 系统调用输出函数，不依赖 libc 的 printf/putchar。
static inline long sys_write(long fd, const void *buf, unsigned long count) {
    long ret;
    asm volatile(
        "syscall"
        : "=a"(ret)
        : "a"(1), "D"(fd), "S"(buf), "d"(count)
        : "rcx", "r11", "memory"
    );
    return ret;
}

int console_putchar(char c, void *context) {
    (void)context;
    sys_write(1, &c, 1);
    return 1;
}

int output_string(const char *str, output_func output, void *context) {
    int count = 0;
    while (str && *str) {
        output(*str++, context);
        count++;
    }
    return count;
}

int int_to_str(int num, char *buf) {
    char temp[12];
    int idx = 0;
    unsigned int value;

    if (num == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return 1;
    }

    if (num < 0) {
        value = (unsigned int)(-num);
    } else {
        value = (unsigned int)num;
    }

    while (value > 0) {
        temp[idx++] = '0' + (value % 10);
        value /= 10;
    }

    if (num < 0) {
        temp[idx++] = '-';
    }

    for (int i = 0; i < idx; i++) {
        buf[i] = temp[idx - 1 - i];
    }
    buf[idx] = '\0';
    return idx;
}

static int handle_string(void **args, output_func output, void *context, int *written) {
    const char *str = (const char *)*args;
    args++;
    *written += output_string(str, output, context);
    return TRUE;
}

static int handle_decimal(void **args, output_func output, void *context, int *written) {
    int value = (int)(long)*args;
    args++;
    char buf[12];
    int len = int_to_str(value, buf);
    (void)len;
    *written += output_string(buf, output, context);
    return TRUE;
}

static format_map dispatch_table[] = {
    {'s', handle_string},
    {'d', handle_decimal},
};

int my_printf(const char *format, void *arg_start, output_func output, void *context) {
    int written = 0;
    void **args = (void **)arg_start;

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == '%') {
                output('%', context);
                written++;
            } else {
                int found = FALSE;
                for (int i = 0; i < (int)(sizeof(dispatch_table) / sizeof(dispatch_table[0])); i++) {
                    if (dispatch_table[i].spec == *format) {
                        dispatch_table[i].handler(args, output, context, &written);
                        args++;
                        found = TRUE;
                        break;
                    }
                }
                if (!found) {
                    output('%', context);
                    output(*format, context);
                    written += 2;
                }
            }
        } else {
            output(*format, context);
            written++;
        }
        format++;
    }

    return written;
}

int main(void) {
    const char *name = "world";
    void *args[] = {(void *)name, (void *)(long)2026};
    my_printf("Hello %s, year=%d%%\n", args, console_putchar, NULL);
    return 0;
}

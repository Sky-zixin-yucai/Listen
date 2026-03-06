#include <stdio.h>

void print_bits(unsigned int x) {
    unsigned int mask = 1u << 30u; // 右移 30 位
    for(unsigned int i = 0; i < 32; ++i) {
        if(x & mask) {
            printf("1");
        } else {
            printf("0");
        }
        mask >>= 1;
    }
    printf("\n");
}

int is_power_of_two(unsigned int x) {
    return x && !(x & (x - 1));
}

int main() {
    unsigned int a = 0, b = 1, c = 2, d = 3, e = 16, f = 255;
    print_bits(a);
    printf("%d\n", is_power_of_two(a));
    print_bits(b);
    printf("%d\n", is_power_of_two(b));
    print_bits(c);
    printf("%d\n", is_power_of_two(c));
    print_bits(d);
    printf("%d\n", is_power_of_two(d));
    print_bits(e);
    printf("%d\n", is_power_of_two(e));
    print_bits(f);
    printf("%d\n", is_power_of_two(f));
    return 0;
}
#include "ft_printf.h"

int main(void) {
    // char: A | string: abcde     |
    ft_printf("char: %c | string: %-10.5s|\n", 'A', "abcdef");

    // d:-123 i:123 u:4294967295
    ft_printf("d:%d i:%i u:%u\n", -123, 123, 4294967295u);

    // hex lower:0xbeef | upper:0XBEEF
    ft_printf("hex lower:%#x | upper:%#X\n", 0xbeef, 0xBEEF);

    // width:      42 | left:42       | zero:00000042 | prec:00042
    ft_printf("width:%8d | left:%-8d | zero:%08d | prec:%.5d\n", 42, 42, 42, 42);

    // ptr:0x16f746854 | null:(nil)
    int x = 7;
    ft_printf("ptr:%p | null:%p\n", &x, NULL);

    // progress: 100%
    ft_printf("progress: 100%%\n");

    int test = 0x012345678;
    ft_printf("%b\n", &test);
    return 0;
}

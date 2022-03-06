#include <stdio.h>

typedef unsigned short u16;

struct desc_struct 
{
    u16 limit0;
    u16 base0;
    u16 base1: 8, type: 4, s: 1, dpl: 2, p: 1;
    u16 limit1: 4, avl: 1, l: 1, d: 1, g: 1, base2: 8;
} __attribute__((packed));

#define GDT_ENTRY_INIT(flags, base, limit)                      \
            {                                                       \
		                .limit0         = (u16) (limit),                \
		                .limit1         = ((limit) >> 16) & 0x0F,       \
		                .base0          = (u16) (base),                 \
		                .base1          = ((base) >> 16) & 0xFF,        \
		                .base2          = ((base) >> 24) & 0xFF,        \
		                .type           = (flags & 0x0f),               \
		                .s              = (flags >> 4) & 0x01,          \
		                .dpl            = (flags >> 5) & 0x03,          \
		                .p              = (flags >> 7) & 0x01,          \
		                .avl            = (flags >> 12) & 0x01,         \
		                .l              = (flags >> 13) & 0x01,         \
		                .d              = (flags >> 14) & 0x01,         \
		                .g              = (flags >> 15) & 0x01,         \
		        }

int main()
{
    struct desc_struct desc = GDT_ENTRY_INIT(0xc0fa, 0, 0xfffff);

    printf("GDT_ENTRY_INIT(0xc0fa, 0, 0xfffff) = %lx\n", *((unsigned long *)(&desc)));

    return 0;
}

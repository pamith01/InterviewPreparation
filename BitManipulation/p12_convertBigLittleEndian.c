#include <stdio.h>
#include <stdint.h>

uint32_t convertEndianness(uint32_t n)
{
    return (((n & 0x000000FFu) << 24) | ((n & 0x0000FF00u) << 8) | 
            ((n & 0x00FF0000u) >> 8) | ((n & 0xFF000000u) >> 24));
}

int main()
{
    uint32_t n = 0x12345678;
    printf("Changed Endianess: 0x%x\n", convertEndianness(n));
    return 0;
}
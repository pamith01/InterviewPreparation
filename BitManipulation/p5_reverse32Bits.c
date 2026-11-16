#include <stdio.h>
#include <stdint.h>

uint32_t reverse32Bits(uint32_t n)
{
    n = ((n & 0xAAAAAAAAu) >> 1) | ((n & 0x55555555u) << 1);
    n = ((n & 0xCCCCCCCCu) >> 2) | ((n & 0x33333333u) << 2);
    n = ((n & 0xF0F0F0F0u) >> 4) | ((n & 0x0F0F0F0Fu) << 4);
    n = ((n & 0xFF00FF00u) >> 8) | ((n & 0x00FF00FFu) << 8);
    return (n >> 16) | (n << 16);
}

int main()
{
    uint32_t num = 0x12345678;
    printf("Reversed Integer: 0x%x\n", reverse32Bits(num));
    return 0;
}

/* 
Time Complexity: O(1)
Space Complexity: O(1)
*/
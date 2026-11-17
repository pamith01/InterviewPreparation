#include <stdio.h>
#include <stdint.h>

uint32_t rotateLeft32(uint32_t v, unsigned n)
{
    n &= 31u;
    return (v << n) | (v >> ((32u - n) & 31u));
}

int main()
{
    printf("Rotated integer: 0x%x\n", rotateLeft32(0x00000001u, 3));
    return 0;
}

/*
Time Complexity: O(1)
Space Complexity: O(1)
*/
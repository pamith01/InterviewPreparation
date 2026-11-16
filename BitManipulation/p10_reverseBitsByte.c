#include <stdio.h>
#include <stdint.h>

uint8_t reverseBitsByte(uint8_t byte)
{
    uint8_t r = 0;
    for (int i = 0;i < 8;i++)
    {
        r = (uint8_t)((r << 1) | (byte & 1u));
        byte>>=1;
    }
    return r;
}

int main()
{
    uint8_t byte = 0xB2;
    printf("Reversed Byte: 0x%x\n", reverseBitsByte(byte));
    return 0;
}

/* 
Time Complexity: O(1)
Space Complexity: O(1)
*/
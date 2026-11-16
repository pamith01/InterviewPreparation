#include <stdio.h>
#include <stdint.h>

int detectMachineEndianness(void)
{
    uint16_t num = 0x7601;
    const uint8_t *p = (const uint8_t*)&num;
    return (*p == 0x01);
}

int main()
{
    printf(detectMachineEndianness()?"Little Endian\n" : "Big Endian\n");
    return 0;
}

/* 
LSB is at lower address in Little Endian
LSB is at higher address in Big Endian
*/
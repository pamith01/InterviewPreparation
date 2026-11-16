#include <stdio.h>
#include <stdint.h>

uint32_t setNthBit(uint32_t reg, int n)
{
    reg |= (1u << n);
    return reg;
}

uint32_t clearNthBit(uint32_t reg, int n)
{
    reg &=~(1U << n);
    return reg;
}

uint32_t toggleNthBit(uint32_t reg, int n)
{
    reg ^=(1U << n);
    return reg;
}

uint32_t readNthBit(uint32_t reg, int n)
{
    return ((reg >> n) & 1u);
}

int main()
{
    int reg = 0xFFFFFFF2;
    int n = 1;
    printf("Set Value: 0x%x\n", setNthBit(reg, n));
    printf("Clear Value: 0x%x\n", clearNthBit(reg, n));
    printf("Toggle Value: 0x%x\n", toggleNthBit(reg, n));
    printf("Read Bit: 0x%x\n", readNthBit(reg, 1));
    return 0;
}

/*
Time Complexity: O(1)
Space Complexity: O(1)
*/
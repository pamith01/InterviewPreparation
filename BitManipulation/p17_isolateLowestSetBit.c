#include <stdio.h>
#include <stdint.h>

uint32_t isolateLowestSetBit(uint32_t v)
{
    return (v & (~v + 1u));
}

int main()
{
    printf("Lowest Bit Set Value: 0x%x\n", isolateLowestSetBit(0x68u));
    return 0;
}

/* 
Time Complexity: O(1)
Space Complexity: O(1)
*/
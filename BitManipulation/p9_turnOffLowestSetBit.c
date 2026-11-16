#include <stdio.h>
#include <stdint.h>

int turnOffLowestSetBit(uint32_t n)
{
    return (n & (n-1u));
}

int main()
{
    int n = 9;
    printf("Clear Lowest Set Bit: %d\n", turnOffLowestSetBit(n));
    return 0;
}

/*
Time Complexity: O(1)
Space Complexity: O(1)
*/
#include <stdio.h>
#include <stdint.h>

/* Regular method */

int countSetBits(uint32_t n)
{
    int count = 0;
    while(n)
    {
        if (n & 1u){
            count++;
        }
        n >>= 1;
    }
    return count;
}

int main()
{
    printf("Set Bits: %d\n", countSetBits(1));
    return 0;
}

/*
Time Complexity: O(n), where n is the number of bits
Space Complexity: O(1) 
*/
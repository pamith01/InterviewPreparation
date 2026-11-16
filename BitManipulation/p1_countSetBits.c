#include <stdio.h>
#include <stdint.h>

/* Brian Kernighan's Method */

int countSetBits(uint32_t n)
{
    int count = 0;
    while(n){
        n &= (n-1);
        count++;
    }
    return count;
}

int main()
{
    printf("Set Bits: %d\n", countSetBits(10));
    return 0;
}

/*
Time Complexity: O(k), where k is the number of set bits
Space Complexity: O(1) 
*/
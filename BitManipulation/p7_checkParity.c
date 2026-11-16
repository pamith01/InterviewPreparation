#include <stdio.h>
#include <stdint.h>

/* Check parity means to check even or odd number of set bits in a number */

uint32_t checkParity(uint32_t n)
{
    n ^= n>>16;
    n ^= n>>8;
    n ^= n>>4;
    n ^= n>>2;
    n ^= n>>1;
    return n&1;
}

int main()
{
    int n = 0xF0;
    printf("No of set bits: %s\n", checkParity(n)? "Odd" : "Even");
    return 0;
}
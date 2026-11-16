#include <stdio.h>

int powerOfTwo(int n)
{
    return (n != 0 && !(n & (n-1)));
}

int main()
{
    int n = 0;
    printf(powerOfTwo(n)?"Is a Power of 2\n" : "Is not a Power of 2\n");
    return 0;
}

/* 
Time Complexity: O(1)
Space Complexity: O(1)
*/
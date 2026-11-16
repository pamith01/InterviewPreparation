#include <stdio.h>
/* 	// Returns the minimum of x and y without branching */
int branchlessMin(int x, int y)
{
    int diff = x - y;
    int mask = diff >> 31;
    return y + (diff & mask);
}

/* 	// Returns the maximum of x and y without branching */
int branchlessMax(int x, int y)
{
    int diff = x - y;
    int mask = diff >> 31;
    return x - (diff & mask);
}

/* 	// Returns the absolute value of n without branching */
int branchlessAbs(int n)
{
    int mask = n >> 31;
    return (n ^ mask) - mask;
}

int main()
{
    printf("Min: %d\n", branchlessMin(9, 10));
    printf("Max: %d\n", branchlessMax(19, 10));
    printf("Abs: %d\n", branchlessAbs(-9));
    return 0;
}
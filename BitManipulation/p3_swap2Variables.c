#include <stdio.h>

void swap2Variables(int* a, int* b)
{
    if (a == NULL || b == NULL) return;
    
    *a = *a ^ *b;
    *b = *b ^ *a;
    *a = *a ^ *b;
}

int main()
{
    int a = 5, b = 10;
    printf("Before Swapping\na: %d, b: %d\n", a, b);
    swap2Variables(&a, &b);
    printf("After Swapping\na: %d, b: %d\n", a, b);
    return 0;
}

/* 
Time Complexity: O(1)
Space Complexity: O(1)
*/
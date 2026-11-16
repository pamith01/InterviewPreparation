#include <stdio.h>

/* Every element should occur only once */

int findUniqueElement(int* arr, int n)
{
    int unique = 0;
    for (size_t i = 0; i < n;i++)
    {
        unique ^= arr[i];
    }
    return unique;
}

int main()
{
    int arr[] = {1,2,1,2,4,4,7};
    printf("Unique Element: %d\n", findUniqueElement(arr, sizeof(arr)/sizeof(arr[0])));
    return 0;
}

/*
Time Complexity: O(n)
Space Complexity: O(1)
*/
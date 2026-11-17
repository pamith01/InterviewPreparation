#include <stdio.h>
#include <string.h>

/* Two pointer approach */

static void reverseString(char* s)
{
    size_t left = 0;
    size_t right = strlen(s)-1;
    while(left < right)
    {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;

        left++;
        right--;
    }
}

int main()
{
    char s[] = "hello";
    reverseString(s);
    printf("Reversed string: %s\n", s);
    return 0;
}

/* 
Time Complexity: O(n)
Space Complexity: O(1)
*/
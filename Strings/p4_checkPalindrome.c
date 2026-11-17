#include <stdio.h>
#include <string.h>

static int checkPalindrome(char* s)
{
    size_t left = 0;
    size_t right = strlen(s);
    while(left < right)
    {
        if (s[left++] != s[--right])
            return 0;
    }
    return 1;
}

int main()
{
    char str[] = "malayalam";
    printf(checkPalindrome(str)?"Is Palindome\n":"Not Palindrome\n");
    return 0;
}

/* 
Time Complexity: O(n)
Space Complexity: O(1)
*/
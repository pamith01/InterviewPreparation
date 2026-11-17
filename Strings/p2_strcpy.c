/* Copy strings from source string to destination */

/* Copy bytes until and including the NULL. The function cannot know the destination size */

#include <stdio.h>
#include <stdint.h>

static char* myStrcpy(char* dest, const char* src)
{
    char* d = dest;
    while ((*d++ = *src++) != '\0'){}
    return dest;
}

int main()
{
    char dest[16];
    printf("Copied string: %s\n", myStrcpy(dest, "qualcomm"));
    return 0;
}

/* 
Time Complexity: O(n)
Space Complexity: O(1)
*/
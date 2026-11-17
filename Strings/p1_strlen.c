/* Implement strlen */
#include <stdio.h>
#include <stdint.h>

static size_t myStrlen(const char* s)
{
    const char* p = s;
    while(*p){
        p++;
    }
    return (size_t)(p - s);
}

int main()
{
    char* s = "embedded";
    printf("Length of string: %ld\n", myStrlen(s));
    return 0;
}

/*
Time Complexity: O(n)
Space Complexity: O(1)
*/
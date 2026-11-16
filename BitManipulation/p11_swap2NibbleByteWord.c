#include <stdio.h>
#include <stdint.h>

uint8_t swap2Nibbles(uint8_t byte)
{
    return (uint8_t)((byte >> 4) | (byte << 4));
}

uint16_t swap2Bytes(uint16_t halfWord)
{
    return (uint16_t)((halfWord >> 8) | (halfWord << 8));
}

uint32_t swap2HalfWords(uint32_t word)
{
    return (uint32_t)((word >> 16) | (word << 16));
}

int main()
{
    uint8_t byte = 0xA5;
    printf("Swapped Byte: 0x%x\n", swap2Nibbles(byte));

    uint16_t halfWord = 0x1234;
    printf("Swapped Halfword: 0x%x\n", swap2Bytes(halfWord));

    uint32_t word = 0x12345678;
    printf("Swapped word: 0x%x\n", swap2HalfWords(word));

    return 0;
}
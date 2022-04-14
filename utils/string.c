#include "string.h"

static void reverse(char str[], u32int length)
{
    u32int start = 0;
    u32int end = length -1;
    while (start < end)
    {
        u32int temp = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = temp;
        start++;
        end--;
    }
}

char *itoa(s32int num, char *buffer, u32int base) {
    u32int i = 0;
    u8int isNegative = 0;
 
    /* Handle 0 explicitly, otherwise empty string is printed for 0*/
    if (num == 0)
    {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        u32int rem = num % base;
        buffer[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        buffer[i++] = '-';
 
    buffer[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(buffer, i);
 
    return buffer;
}

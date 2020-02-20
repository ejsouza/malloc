#include "../includes/malloc.h"

void        number_to_hex(uint64_t numb, int base)
{
    uint64_t    remainder;
    int         i;
    char        number[42];
    char        hex[] = "0123456789abcdef";

    number[0] = '0';
    number[1] = 'x';
    i = 10;
    while (numb != 0)
    {
        remainder = numb % base;
        if (remainder < 10)
            number[i--] = 48 + remainder;
        else
            number[i--] = hex[remainder];
        numb /= base;
    }
    number[11] = 0;
    ft_putstr(number);
}
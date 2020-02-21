#include "../includes/malloc.h"

static void reverse_numb(char *nb)
{
    int  len;
    size_t  i;
    char    number[20];

    len = ft_strlen(nb) - 1;
    i = 0;
    while (len >= 0)
    {
        number[i] = nb[len];
        i++;
        len--;
    }
    number[i] = 0;
    ft_putstr(number);
}

void        put_number(uint64_t number)
{
    char    numb[20];
    int     i;
    uint64_t    max_val;
    uint64_t remainder;
    size_t      len;

    i = 0;
    remainder = 0;
    max_val = (uint64_t)1844674407370955161;
    if (number > max_val)
        return ;
    while (number != 0)
    {
        remainder = number % 10;
        numb[i] = remainder + 48;
        number /= 10;
        i++;
    }
    numb[i] = 0;
    len = ft_strlen(numb);
    reverse_numb(numb);
}

void        number_to_hex(uint64_t numb, int base)
{
    uint64_t    remainder;
    int         i;
    char        number[42];
    char        hex[17];
    
    ft_memcpy(hex, "0123456789ABCDEF", 16);
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
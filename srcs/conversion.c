/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:18:49 by esouza            #+#    #+#             */
/*   Updated: 2020/02/21 15:18:54 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void        print_itoa(int nb)
{
    char    numb[15];
    int     i;
    int     reminder;
    int     nb_len;

    ft_bzero(numb, 15);
    nb_len = int_len(nb);
    ft_putstr("\nint len = ");
    put_number(nb_len);
    ft_putstr("\n");
    // i = (nb < 0) ? 1 : 0;
    // numb[0] = (i == 1) ? '-' : '\0';
    i = 0;
    // if (nb < 0)
    // {
    //     numb[i++] = '-';
    //     nb_len--;
    // }
    while (nb_len != i)
    {
        // put_number(nb_len);
        // ft_putstr("\n");
        reminder = nb % 10;
        numb[nb_len] = reminder + '0';
        // ft_putstr(&numb[nb_len]);
        // ft_putstr("\n");
        nb /= 10;
        nb_len--;
    }
    ft_putstr("\n===============================\n");
    ft_putstr(numb);
    ft_putstr("===============================\n");
}

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

    if (number == 0)
    {
        ft_putstr("0");
        return ;
    }
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

void        to_hex(uint64_t numb)
{
    uint64_t    remainder;
    int         i;
    char        number[42];
    char        hex[17];

    ft_memcpy(hex, "0123456789ABCDEF", 16);
    ft_bzero(number, 42);
    i = 0;
    while (i < 42)
    {
        number[i++] = '0';
    }
    i = 7;
    while (numb != 0)
    {
        remainder = numb % 16;
        if (remainder < 10)
            // number[i++] = 48 + remainder;
           number[i--] = 48 + remainder;
        else
            // number[i++] = hex[remainder];
           number[i--] = hex[remainder];
        numb /= 16;
    }
    number[8] = 0;
    ft_putstr(number);
}

void        number_to_hex(uint64_t numb, int base)
{
    uint64_t    remainder;
    int         i;
    char        number[42];
    char        hex[17];
    
    ft_memcpy(hex, "0123456789ABCDEF", 16);
    ft_bzero(number, 42);
    number[0] = '0';
    number[1] = 'x';
    i = 10;
    //i = 2;
    while (numb != 0 && i < 42)
    {
        remainder = numb % base;
        if (remainder < 10)
            // number[i++] = 48 + remainder;
           number[i--] = 48 + remainder;
        else
            // number[i++] = hex[remainder];
           number[i--] = hex[remainder];
        numb /= base;
    }
    number[11] = 0;
    ft_putstr(number);
}

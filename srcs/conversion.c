/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:18:49 by esouza            #+#    #+#             */
/*   Updated: 2020/03/09 11:03:22 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		reverse_numb(char *nb)
{
	int			len;
	size_t		i;
	char		number[20];

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

void			put_number(uint64_t number)
{
	char		numb[48];
	int			i;
	// uint64_t	max_val;
	uint64_t	remainder;
	size_t		len;

	if (number == 0)
	{
		ft_putstr("0");
		return ;
	}
	i = 0;
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

void			to_hex(uint64_t numb)
{
	uint64_t	remainder;
	int			i;
	char		number[42];
	char		hex[17];

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
			number[i--] = 48 + remainder;
		else
			number[i--] = hex[remainder];
		numb /= 16;
	}
	number[8] = 0;
	ft_putstr(number);
}

void			print_details(size_t *total_size)
{
	if (*total_size)
	{
		ft_putstr("Total : ");
		put_number((*total_size));
		ft_putstr(" octets\n");
	}
}

void			number_to_hex(uint64_t numb, int base)
{
	uint64_t	remainder;
	int			i;
	char		number[42];
	char		hex[17];

	ft_memcpy(hex, "0123456789ABCDEF", 16);
	ft_bzero(number, 42);
	number[0] = '0';
	number[1] = 'x';
	i = 10;
	while (numb != 0 && i < 42)
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

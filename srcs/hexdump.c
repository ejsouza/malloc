/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:10:08 by esouza            #+#    #+#             */
/*   Updated: 2020/03/09 13:23:44 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void			ascii_to_hex(uint64_t numb)
{
	uint64_t		remainder;
	int				i;
	char			number[42];
	char			hex[17];

	ft_memcpy(hex, "0123456789ABCDEF", 16);
	ft_bzero(number, 42);
	ft_bzero(number, 42);
	i = 1;
	while (numb != 0)
	{
		remainder = numb % 16;
		if (remainder < 10)
			number[i--] = 48 + remainder;
		else
			number[i--] = hex[remainder];
		numb /= 16;
	}
	number[2] = 0;
	ft_putstr(number);
	ft_putstr(" ");
}

static void			write_char_hex(void *ptr)
{
	unsigned char	*hex;
	int				i_char;
	int				i;
	int				index;
	uint64_t		head;

	index = 0;
	hex = ptr;
	while (hex[index])
	{
		head = index;
		to_hex(head);
		ft_putstr(" ");
		i = 0;
		while (hex[index + i] && i < 16)
		{
			i_char = (int)hex[index + i];
			ascii_to_hex(i_char);
			i++;
			if (hex[index + i] == 0)
				return ;
		}
		ft_putstr("\n");
		index += i;
	}
}

static void			print_chunk_dump(t_chunk *chunk)
{
	void			*ptr;
	size_t			size;
	unsigned char	*character;

	size = chunk->size;
	ptr = (void *)chunk + sizeof(t_chunk);
	character = ptr;
	number_to_hex((uint64_t)ptr, 16);
	ft_putstr("\n");
	write_char_hex(character);
	ft_putstr("\n");
}

void				hexdump(void)
{
	t_block			*head;
	t_chunk			*chunk;
	int				index;

	head = NULL;
	index = -1;
	while (++index < NB_ZONE)
	{
		head = g_zone[index];
		while (head != NULL)
		{
			chunk = (void *)head + sizeof(t_block);
			while (chunk != NULL)
			{
				if (!chunk->free)
					print_chunk_dump(chunk);
				chunk = (t_chunk *)chunk->next;
			}
			head = head->next;
		}
	}
}

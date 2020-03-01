/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:50:53 by esouza            #+#    #+#             */
/*   Updated: 2020/02/11 10:51:09 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t	malloc_base_16(size_t size)
{
	size_t		remainder;

	if (size < MIN_SIZE_ALLOC)
		return (MIN_SIZE_ALLOC);
	remainder = size % MIN_SIZE_ALLOC;
	if (remainder)
	{
		size += MIN_SIZE_ALLOC - remainder;
	}
	return (size);
}

size_t	round_block(size_t size)
{
	size_t	number_pages;
	size_t	page_size;
	size_t	number_block;

	page_size = getpagesize();
	number_block = getpagesize();
	number_pages = 1;
	while ((size + sizeof(t_block)) > number_block)
	{
		number_block += page_size;
		number_pages++;
	}
	return (number_pages - ONE);
}

static void	*allocator(size_t size, short index)
{
	void		*zone;
	t_block		*tmp;
	size_t		size_zone;
	size_t		number_page;
	size_t		page_size;

	size_zone = index == 0 ? T_ZONE : S_ZONE;
	page_size = getpagesize();
	if (index == LARGE)
		number_page = round_block(size);
	else
	{
		number_page = page_size / size_zone;
		number_page = MIN_ALLOC / number_page;
	}
	number_page++;
	zone = mmap(NULL, number_page * page_size, PROT_READ
				| PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (zone == NULL || zone == MAP_FAILED)
		return (NULL);
	tmp = zone;
	tmp->blc_size = (number_page * page_size) - sizeof(t_block);
	return (zone);
}


void	init_chunk(t_chunk **chunk, size_t size)
{
	(*chunk)->free = 1;
	(*chunk)->size = size;
	(*chunk)->next = NULL;
	(*chunk)->prev = NULL;
}

void	*alloc_handler(size_t size, short index)
{
	void	*addr;
	t_block	*new_zone;

	addr = NULL;
	if (g_zone[index] == NULL)
		addr = NULL;
	else if (index != TWO)
		addr = find_free_space(size, index);
	new_zone = NULL;
	if (addr == NULL)
	{
		if (((new_zone = allocator(size, index)) == NULL))
			return (NULL);
			addr = link_zones(new_zone, size, index);
	}
	return (addr);
}

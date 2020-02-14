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

size_t	round_block(size_t size)
{
	size_t	number_pages;
	//size_t reminder;
	size_t	page_size;

	page_size = getpagesize();
	number_pages = size / page_size;
	// reminder = size % page_size;
	// if (reminder)
	// 	number_pages++;
	return (number_pages);
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
	printf("NUMBER PAGE %zu\n", number_page);
	zone = mmap(NULL, number_page * page_size, PROT_READ
				| PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (zone == NULL || zone == MAP_FAILED)
		return (NULL);
	tmp = zone;
	tmp->blc_size = (number_page * page_size) - sizeof(t_block);
	printf("allocator(%p) \t block_size %zu\n", zone, tmp->blc_size);
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
	t_chunk *tmp; // todelete

	if (g_zone[index] == NULL || index == TWO)
		addr = NULL;
	else
		addr = find_free_space(size, index);
	new_zone = NULL;
	if (addr == NULL)
	{
		if (((new_zone = allocator(size, index)) == NULL))
			return (NULL);
		addr = link_zones(new_zone, size, index);
	}
	tmp = (t_chunk *)addr;
	return (addr);
}

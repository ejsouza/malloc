/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hanlder_request.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:25:27 by esouza            #+#    #+#             */
/*   Updated: 2019/11/06 14:40:19 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static short	zone_size(size_t size)
{
	if (size <= T_ZONE)
		return (TINY);
	else if (size <= S_ZONE)
		return (SMALL);
	return (LARGE);
}

static void		initialize_zone(t_block *zone, int size_zone)
{
	zone->next = NULL;
	zone->block_size = size_zone * MIN_ALLOC;
	zone->start = zone;
}

t_block		*malloc_zone(short index)
{
	t_block		*zone;
	int			size_zone;

	size_zone = index == 0 ? T_ZONE : S_ZONE;
	zone = (t_block *) mmap(NULL, size_zone * MIN_ALLOC, PROT_READ
				| PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (zone != MAP_FAILED && zone != NULL)
		initialize_zone(zone, size_zone);
	return (zone);
}

static void		link_block(t_block *addr, t_block *zone[NB_ZONE], short index)
{
	t_block		*tmp;
	int			i;

	tmp = zone[index];
	i = 0;
	while (zone[index]->next != NULL)
	{
		i++;
		zone[index] = zone[index]->next;
	}
	zone[index]->next = addr;
	zone[index] = tmp;
	printf("i = %d\tblock_size %zu\n", i, zone[index]->block_size);
	printf("--------------ADDRESS---------------\n");
	printf("zone[%p]\n", zone[index]);
	printf("size[%p]\n", &zone[index]->block_size);
	printf("------------------------------------\n");
}

void			*handler_request(size_t size, t_block *zone[NB_ZONE])
{
	short		index;
	t_block		*addr;

	addr = NULL;
	index = zone_size(size);
	if (zone[index] == NULL && index != LARGE)
	{
		addr = malloc_zone(index);
		zone[index] = addr;
	}
	else if (index == LARGE)
	{
		printf("Not handled the LARGE yet\n");
		return (NULL);
	}
	else
	{
		addr = malloc_zone(index);
		if (addr != NULL && addr != MAP_FAILED)
			link_block(addr, zone, index);
	}
	return (addr);
}

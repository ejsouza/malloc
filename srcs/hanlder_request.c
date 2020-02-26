/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hanlder_request.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:25:27 by esouza            #+#    #+#             */
/*   Updated: 2019/11/12 12:49:58 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

short	zone_size(size_t size)
{
	if (size <= T_ZONE)
		return (TINY);
	else if (size <= S_ZONE)
		return (SMALL);
	return (LARGE);
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
	//printf("i = %d\tblock_size %zu\n", i, zone[index]->block_size);
//	printf("--------------ADDRESS---------------\n");
	// printf("zone[%p]\n", zone[index]);
	// printf("strt[%p]\n", zone[index]->start);
	// printf("size[%p]\n", &zone[index]->block_size);
	// printf("------------------------------------\n");
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
		// printf("Not handled the LARGE yet\n");
		return (NULL);
	}
	else
	{
		addr = malloc_zone(index);
		if (addr == NULL || addr == MAP_FAILED)
			return (NULL);
		link_block(addr, zone, index);
	}
	return (addr->start);
}

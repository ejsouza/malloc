/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_zones.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:52:39 by esouza            #+#    #+#             */
/*   Updated: 2020/02/11 10:52:46 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*link_zones(t_block *new_zone, size_t size, short index)
{
	t_block		*current;
	t_chunk		*chunk;
	void		*addr;

 	new_zone->next = NULL;
	new_zone->blc_size -= (size + sizeof(t_chunk));
	if (g_zone[index] == NULL)
	{
		g_zone[index] = new_zone;
		g_zone[index]->next = NULL;
		current = g_zone[index];
	}
	else if (index != TWO)
	{
		current = g_zone[index];
		while (current->next != NULL)
			current = current->next;
		current->next = new_zone;
	}
	addr = NULL;
	/*
	** addr = new_zone and not addr = current otherwise it will not work, cuz it will always give memory
	** from the first "BLOCK" (aka) g_zone[index]
	*/
	addr = new_zone + ONE;
	chunk = addr;
	init_chunk_header(&chunk, size);
	addr = chunk + ONE;
	return (addr);
}

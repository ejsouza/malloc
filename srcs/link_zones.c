/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_zones.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:52:39 by esouza            #+#    #+#             */
/*   Updated: 2020/03/09 13:27:41 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		create_first_chunk(t_chunk *chunk, size_t size
		, t_block *head)
{
	t_chunk		*new_chunk;
	void		*tmp;

	head->blc_size -= size + (sizeof(t_chunk) * 2);
	tmp = (void *)chunk + size + sizeof(t_chunk);
	new_chunk = tmp;
	new_chunk->free = 1;
	new_chunk->size = head->blc_size;
	new_chunk->next = NULL;
	new_chunk->prev = chunk;
	chunk->free = 0;
	chunk->size = size;
	chunk->next = (void *)new_chunk;
	chunk->prev = NULL;
}

int				is_pointer_valid(void *ptr)
{
	if (loop_through_block(ptr, 0))
	{
		return (1);
	}
	if (loop_through_block(ptr, 1))
	{
		return (1);
	}
	if (loop_through_block(ptr, 2))
	{
		return (1);
	}
	return (0);
}

void			coalesce(t_chunk *curr, t_chunk *neighbor)
{
	t_chunk		*start;
	t_chunk		*tmp;

	start = NULL;
	if (curr < neighbor)
	{
		start = curr;
		if ((tmp = (t_chunk *)neighbor->next) != NULL)
			tmp->prev = start;
		start->free = 1;
		start->size += (neighbor->size + sizeof(t_chunk));
		start->next = (void *)tmp;
		bzero_chunk(neighbor);
	}
	else if (curr > neighbor)
	{
		start = neighbor;
		if ((tmp = (t_chunk *)curr->next) != NULL)
			tmp->prev = start;
		start->free = 1;
		start->size += (curr->size + sizeof(t_chunk));
		start->next = (void *)tmp;
		bzero_chunk(curr);
	}
}

void			bzero_chunk(t_chunk *chunk)
{
	chunk->next = NULL;
	chunk->prev = NULL;
	chunk->free = 1;
}

/*
** addr = new_zone and not addr = current otherwise it will not work, cuz it
** will always give memory from the first "BLOCK" (aka) g_zone[index]
*/

void			*link_zones(t_block *new_zone, size_t size, short index)
{
	t_block		*current;
	t_chunk		*chunk;
	void		*addr;

	new_zone->next = NULL;
	if (g_zone[index] == NULL)
	{
		g_zone[index] = new_zone;
		g_zone[index]->next = NULL;
		current = g_zone[index];
	}
	else
	{
		current = g_zone[index];
		while (current->next != NULL)
			current = current->next;
		current->next = new_zone;
	}
	addr = NULL;
	addr = new_zone + ONE;
	chunk = addr;
	create_first_chunk(chunk, size, new_zone);
	addr = chunk + ONE;
	return (addr);
}

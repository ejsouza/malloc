/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_free_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:51:40 by esouza            #+#    #+#             */
/*   Updated: 2020/02/11 10:51:48 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/malloc.h"

static void		is_chunk_free(t_chunk **curr, void **addr, size_t size)
{
	if ((*curr)->size == size)
	{
		(*curr)->free = 0;
		*addr = (*curr) + ONE;
	}
	else if ((*curr)->size > (size + sizeof(t_chunk)) && (*curr)->next == NULL)
		*addr = split_chunk(*curr, size);
	else if ((*curr)-> size > (size + sizeof(t_chunk)) && (*curr)->next != NULL)
		*addr = split_to_middle(*curr, size);
	else
	*curr = (t_chunk *)(*curr)->next;
}

static void	*find_chunk(t_chunk **chunk, size_t size, t_block *start)
{
	void	*addr;
	t_chunk	*curr;

	addr = NULL;
	curr = (*chunk);
	while (curr != NULL)
	{
		if (curr->free)
		{
			is_chunk_free(&curr, &addr, size);
		}
		else
			curr = (t_chunk *)curr->next;
		if (addr != NULL)
		{
			start->blc_size -= size + sizeof(t_chunk);
			return (addr);
		}
	}
	return (addr);
}

void	*find_free_space(size_t size, short index)
{
	t_block		*current;
	t_block		*tmp;
	t_chunk		*chunk;
	void		*addr;

	current = g_zone[index];
	while (current != NULL)
	{
		if (current->blc_size < (size + sizeof(t_chunk)))
		{
			current = current->next;
			continue;
		}	
		tmp = current + ONE;
		chunk = (t_chunk *)tmp;
		addr = find_chunk(&chunk, size, current);
		if (addr != NULL)
			return (addr);
		// This line doesn't seems to need it
		current = current->next;
	}
	return (NULL);
}

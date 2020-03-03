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

// static size_t	return_max_position(index)
// {
// 	if (index == 0)
// 		return (26 * 4096);
// 	else if (index == 1)
// 		return (101 * 4096);
// 	return (0);
// }

static void		is_chunk_free(t_chunk **curr, void **addr, size_t size)
{
	if ((*curr)->size == size)
	{
		(*curr)->free = 0;
		*addr = (*curr) + ONE;
	}
	else if ((*curr)->size > (size + sizeof(t_chunk)) && (*curr)->next == NULL)
	{
		/*
		** before calling split to end;
		** better check for enough space for size plus sizeof(t_chunk) plus some
		** minimum for the last chunk on the list;
		*/
		*addr = split_chunk(*curr, size);
	}
	else if ((*curr)-> size > (size + sizeof(t_chunk)) && (*curr)->next != NULL)
		*addr = split_to_middle(*curr, size);
	else
	{
		*curr = (t_chunk *)(*curr)->next;
	}
}

static void	*find_chunk(t_chunk **chunk, size_t size, t_block *start, int index)
{
	void	*addr;
	t_chunk	*curr;
	//size_t	address;
	//address = return_max_position(index);
	//if (!address)
		// address = size;
	if (index)
		;
	addr = NULL;
	curr = (*chunk);
	while (curr != NULL)
	{
		if (curr->free && (((size_t)curr + size + 32 + MIN_SIZE_ALLOC * 2) <= curr->size))
		{
			is_chunk_free(&curr, &addr, size);
			if (addr != NULL)
			{
				start->blc_size -= size + sizeof(t_chunk);
				return (addr);
			}
		}
		else
			curr = (t_chunk *)curr->next;
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
		addr = find_chunk(&chunk, size, current, index);
		if (addr != NULL)
			return (addr);
		// This line doesn't seems to need it
		current = current->next;
	}
	return (NULL);
}

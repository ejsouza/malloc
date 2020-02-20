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


// void	size_header_update(t_chunk *curr)
// {
// 	t_block		*head;
// 	t_chunk		*current;
// //	t_chunk		*tmp;
// 	size_t		size;

// 	size = curr->size;
// 	current = curr;
// //	tmp = current; 
// 	while(current->prev != NULL)
// 	{
// 		current = current->prev;
// 	}
// //	while (tmp->prev != NULL)
// //	{
// //		tmp = tmp->prev;
// //	}
// 	head = (t_block *)current - ONE;
// 	head->blc_size += curr->size;
// }

// void	*init_chunk_header(t_chunk **chunk, size_t size)
// {
// 	t_chunk	*tmp_chunk;
// 	void	*tmp_void;
// 	t_chunk *addr;
// 	size_t	plus_bytes;

// 	plus_bytes = sizeof(t_chunk);
// 	tmp_void = (void *)(*chunk);
// 	addr = tmp_void + plus_bytes; // ok
// 	tmp_chunk = (void *)addr + size;
// 	init_chunk(&tmp_chunk, 0);
// 	(*chunk)->size = size;
// 	(*chunk)->next = (void *)(tmp_chunk);
// 	(*chunk)->free = 0;
// 	tmp_chunk->prev = (*chunk);
// 	return (addr);
// }

// static t_chunk	*loop_through_chunk(t_chunk *curr, size_t size, int index, t_block *start)
// {
// 	void	*addr;
// 	t_chunk	*chunk;

// 	chunk = curr;
// 	addr = NULL;
// 	while (chunk != NULL)
// 	{
// 		if (chunk->free)
// 		{
// 			if (chunk->size ==  size)
// 			{
// 				chunk->free = 0;
// 				addr = curr + ONE;
// 			}
// 			else if (chunk)
// 				;
// 			else if (chunk)
// 				;
// 			else
// 				chunk =  (t_chunk *)chunk->next;
// 		}
// 		else
// 			chunk = (t_chunk *)chunk->next;
// 		if (addr != NULL)
// 		{
// 			start->blc_size -= size + sizeof(t_chunk);
// 			return (addr);
// 		}
// 	}
// 	return (addr);
// }

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

//static void	*find_chunk(t_chunk **chunk, size_t size, short index, t_block *start)
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
			// if (curr->size == size)
			// {
			// 	curr->free = 0;
			// 	addr = curr + ONE;
			// }
			// else if (curr->size > (size + sizeof(t_chunk)) && curr->next == NULL)
			// 	// Pay attention to the end of the block
			// 	addr = split_chunk(curr, size);
			// else if (curr->size > (size + sizeof(t_chunk)) && curr->next != NULL)
			// 	addr = split_to_middle(curr, size);
			// else
			// 	curr = (t_chunk *)curr->next;
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

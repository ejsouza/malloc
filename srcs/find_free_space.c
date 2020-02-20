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
#include <stdlib.h> // todelete 

void		update_size_block_head(t_chunk *start)
{
	t_chunk	*curr;
	size_t 	size;
	t_block *head_block;

	if (start == NULL)
		return ;
	size = start->size;
	curr = start;
	while (curr->prev != NULL)
		curr = curr->prev;
	head_block = (t_block *)curr - ONE;
	head_block->blc_size += size + sizeof(t_chunk);
}

void	size_header_update(t_chunk *curr)
{
	t_block		*head;
	t_chunk		*current;
//	t_chunk		*tmp;
	size_t		size;

	size = curr->size;
	current = curr;
//	tmp = current; 
	while(current->prev != NULL)
	{
		current = current->prev;
	}
//	while (tmp->prev != NULL)
//	{
//		tmp = tmp->prev;
//	}
	head = (t_block *)current - ONE;
	head->blc_size += curr->size;
}

void	*init_chunk_header(t_chunk **chunk, size_t size)
{
	t_chunk	*tmp_chunk;
	void	*tmp_void;
	t_chunk *addr;
	size_t	plus_bytes;

	plus_bytes = sizeof(t_chunk);
	tmp_void = (void *)(*chunk);
	addr = tmp_void + plus_bytes; // ok
	tmp_chunk = (void *)addr + size;
	init_chunk(&tmp_chunk, 0);
	(*chunk)->size = size;
	(*chunk)->next = (void *)(tmp_chunk);
	(*chunk)->free = 0;
	tmp_chunk->prev = (*chunk);
	return (addr);
}

static void	*find_chunk(t_chunk **chunk, size_t size, short index, t_block *start)
{
	void	*addr;
	size_t	base;
	int	size_pages;
	t_chunk	*curr;

	size_pages = (index == TINY) ? PAGES_T : PAGES_S;
	addr = NULL;
	base = (size_t)start;
	curr = (*chunk);
	while (curr != NULL)
	{
		if (curr->free)
		{
			if (curr->size == size)
			{
				curr->free = 0;
				addr = curr + ONE;
			}
			else if (curr->size > (size + sizeof(t_chunk)) && curr->next == NULL)
				// Pay attention to the end of the block
				addr = split_chunk(curr, size);
			else if (curr->size > (size + sizeof(t_chunk)) && curr->next != NULL)
				addr = split_to_midlle(curr, size);
			else
				curr = (t_chunk *)curr->next;
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
		addr = find_chunk(&chunk, size, index, current);
		if (addr != NULL)
			return (addr);
		// This line doesn't seems to need it
		current = current->next;
	}
	return (NULL);
}

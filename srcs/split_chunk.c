/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_chunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:11:22 by esouza            #+#    #+#             */
/*   Updated: 2020/03/10 09:48:02 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void			*split_chunk(t_chunk *chunk, size_t size)
{
	t_chunk		*curr;
	t_chunk		*new_chunk;
	size_t		total_size;
	void		*tmp;

	curr = chunk;
	total_size = curr->size;
	tmp = (void *)curr + size + sizeof(t_chunk);
	new_chunk = tmp;
	new_chunk->free = 1;
	new_chunk->prev = curr;
	new_chunk->next = NULL;
	curr->next = (void *)new_chunk;
	curr->free = 0;
	curr->size = size;
	new_chunk->size = ((total_size - size) - sizeof(t_chunk));
	return (curr + ONE);
}

void			*split_to_middle(t_chunk *curr, size_t size)
{
	t_chunk		*new_chunk;
	void		*tmp;

	tmp = (void *)curr + size + sizeof(t_chunk);
	new_chunk = tmp;
	new_chunk->size = curr->size - (size + sizeof(t_chunk));
	new_chunk->free = 1;
	new_chunk->prev = curr;
	new_chunk->next = curr->next;
	curr->next = (void *)new_chunk;
	curr->free = 0;
	curr->size = size;
	return (curr + ONE);
}

static void		*found_fit(void *ptr, size_t size, size_t size_cp)
{
	void		*addr;

	addr = NULL;
	if ((addr = malloc(size)) == NULL)
		return (ptr);
	ft_memmove(addr, ptr, size_cp);
	free(ptr);
	return (addr);
}

static void		*split_create_new(t_chunk *start, size_t size)
{
	t_chunk		*next;
	t_chunk		*new_chunk;
	void		*tmp;
	size_t		total_size;
	t_block		*head;

	next = (t_chunk *)start->next;
	total_size = (start->size - size) - sizeof(t_chunk);
	tmp = (void *)start + size + sizeof(t_chunk);
	new_chunk = tmp;
	new_chunk->free = 1;
	new_chunk->size = total_size;
	new_chunk->next = (void *)next;
	new_chunk->prev = start;
	if (next != NULL)
		next->prev = new_chunk;
	start->next = (void *)new_chunk;
	start->size = size;
	while (next->prev)
		next = next->prev;
	head = (void *)next - sizeof(t_block);
	head->blc_size += total_size;
	return (start + ONE);
}

/*
** In the else if (size <= curr->size && same_index(size, curr->size))
** There is not enough space left to create a new_chunk, so just
** add them together.
*/

void			*realloc_handler(void *ptr, size_t size, int index)
{
	void		*tmp;
	void		*addr;
	t_chunk		*curr;
	t_chunk		*next;
	int			times;

	times = (index == 0) ? 1 : 32;
	tmp = ptr - sizeof(t_chunk);
	curr = (t_chunk *)tmp;
	next = (t_chunk *)curr->next;
	addr = NULL;
	if (size_what_index(size, curr->size))
		return (found_fit(ptr, size, curr->size));
	else if (size <= curr->size && same_index(size, curr->size))
	{
		if ((curr->size - size) > (sizeof(t_chunk) + (MIN_SIZE_ALLOC * times)))
			addr = split_create_new(curr, size);
		else
			return (ptr);
	}
	else
		addr = enlarge_mem(curr, next, size, times);
	return (addr);
}

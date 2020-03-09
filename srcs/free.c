/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:52:12 by esouza            #+#    #+#             */
/*   Updated: 2020/03/09 12:28:17 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void			free_ptr(t_chunk *ptr)
{
	t_chunk			*curr;
	t_chunk			*tmp;
	t_block			*head_block;

	curr = ptr;
	tmp = curr;
	curr->free = 1;
	while (curr->prev != NULL)
		curr = curr->prev;
	head_block = (t_block *)curr - ONE;
	head_block->blc_size += ptr->size + sizeof(t_chunk);
}

static int			neighbor_is_free(t_chunk *ptr)
{
	t_chunk			*prev;
	t_chunk			*curr;
	t_chunk			*next;
	int				flag;

	flag = 0;
	prev = ptr->prev;
	curr = ptr;
	next = (t_chunk *)ptr->next;
	if (next != NULL && next->free && next->next != NULL)
	{
		coalesce(curr, next);
		flag = 1;
	}
	if (prev != NULL && prev->free)
	{
		coalesce(curr, prev);
		flag = 1;
	}
	return (flag);
}

int					loop_through_block(void *ptr, int index)
{
	void			*tmp;
	t_block			*block;
	t_chunk			*curr;

	block = g_zone[index];
	while (block != NULL)
	{
		tmp = block + ONE;
		curr = (t_chunk *)tmp;
		while (curr != NULL)
		{
			if ((void *)curr + sizeof(t_chunk) == ptr && !curr->free)
				return (1);
			curr = (t_chunk *)curr->next;
		}
		block = block->next;
	}
	return (0);
}

static void			free_twin(void *ptr)
{
	t_chunk			*curr;
	t_chunk			*next;
	t_chunk			*tmp;
	t_block			*block_head;
	size_t			size_ptr_to_free;

	if (ptr == 0 || !is_pointer_valid(ptr))
		return ;
	curr = (t_chunk *)ptr - ONE;
	next = curr;
	size_ptr_to_free = curr->size;
	tmp = curr;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	while (next->next != NULL)
		next = (t_chunk *)next->next;
	block_head = (t_block *)tmp - ONE;
	if (!neighbor_is_free(curr))
		free_ptr(curr);
	else
		block_head->blc_size += size_ptr_to_free + sizeof(t_chunk);
	if (next->size != block_head->blc_size)
		next->size = block_head->blc_size;
	if (check_block_header(block_head->blc_size, size_ptr_to_free))
		free_block(block_head, size_ptr_to_free);
}

void				free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	free_twin(ptr);
	pthread_mutex_unlock(&g_mutex);
}

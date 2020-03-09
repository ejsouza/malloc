/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:51:56 by esouza            #+#    #+#             */
/*   Updated: 2020/03/09 12:18:13 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		index_one(t_block *head, int *c_block, int *c_free)
{
	size_t		size_head;
	t_block		*curr_head;

	curr_head = head;
	size_head = (101 * getpagesize()) - sizeof(t_block) - sizeof(t_chunk);
	while (curr_head != NULL)
	{
		if (curr_head->blc_size >= S_ZONE && curr_head->blc_size < size_head)
		{
			*c_free += 1;
		}
		*c_block += 1;
		curr_head = curr_head->next;
	}
}

/*
** The else in the free_this_block() is for index == 2
** As I always create an independent block for the LARGE
** Just return 1 (i.e) when is a LARGE chunk, always call mmap();
*/

static int		free_this_block(short index)
{
	t_block		*head;
	int			count_block;
	int			count_free;
	size_t		size_head;

	count_block = 0;
	count_free = 0;
	head = g_zone[index];
	if (index == 0)
	{
		size_head = (26 * getpagesize()) - sizeof(t_block) - sizeof(t_chunk);
		while (head != NULL)
		{
			if (head->blc_size >= T_ZONE && head->blc_size < size_head)
				count_free++;
			count_block++;
			head = head->next;
		}
	}
	else if (index == 1)
		index_one(head, &count_block, &count_free);
	else
		return (1);
	return (count_block > 1 && count_free);
}

int				check_block_header(size_t size_head, size_t size_to_free)
{
	short		index;

	index = size_to_free <= T_ZONE ? 0 : 1;
	if (size_to_free > S_ZONE)
		return (free_this_block(TWO));
	else if (index == 1 && size_head
			== ((101 * getpagesize()) - sizeof(t_chunk) - sizeof(t_block)))
	{
		return (free_this_block(index));
	}
	else if (index == 0 && size_head
			== ((26 * getpagesize()) - sizeof(t_chunk) - sizeof(t_block)))
	{
		return (free_this_block(index));
	}
	return (0);
}

/*
** Delete the variable int error;
*/

void			free_block(t_block *block_head, size_t size)
{
	int			size_block;
	int			index;

	size_block = round_block(size);
	size_block++;
	index = size <= T_ZONE ? 0 : 1;
	if (size > S_ZONE)
		index = 2;
	if (index == 2)
	{
		unlink_zone(block_head, index);
		munmap(block_head, block_head->blc_size + sizeof(t_block)
				+ sizeof(t_chunk));
	}
	else if (index == 1)
	{
		if (unlink_zone(block_head, index))
			munmap(block_head, 101 * getpagesize());
	}
	else if (index == 0)
	{
		if (unlink_zone(block_head, index))
			munmap(block_head, 26 * getpagesize());
	}
}

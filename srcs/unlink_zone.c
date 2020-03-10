/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_zone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:47:22 by esouza            #+#    #+#             */
/*   Updated: 2020/03/10 10:23:02 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
** This function name was changed for the norme;
** It finds the lenght of blocks => block_len()
*/

static size_t	b_len(int index)
{
	t_block		*curr;
	size_t		len;

	curr = g_zone[index];
	len = 0;
	while (curr != NULL)
	{
		curr = curr->next;
		len++;
	}
	return (len);
}

static int		space_in_block(t_block *block, int index)
{
	size_t		min_left;

	min_left = index == 0 ? T_ZONE : S_ZONE;
	min_left += sizeof(t_chunk) * 2;
	if (block->blc_size > min_left)
		return (1);
	return (0);
}

/*
** Changed variables name to make function on the norm
** count => c
** index => idx
*/

static int		unlink_this(t_block *targ, t_block *prev, int idx
		, size_t c)
{
	t_block		*tmp;

	if (c == 0 && targ == prev && idx == TWO)
	{
		if (targ->next == NULL)
			g_zone[idx] = NULL;
		else
			g_zone[idx] = targ->next;
	}
	else if (c == 0 && targ == prev && b_len(idx) > 1 && targ->next != NULL)
	{
		if (!space_in_block(targ->next, idx))
			return (0);
		g_zone[idx] = targ->next;
		targ = NULL;
	}
	else if (c == (b_len(idx) - ONE))
		prev->next = NULL;
	else
	{
		tmp = targ->next;
		prev->next = tmp;
		targ = NULL;
	}
	return (1);
}

int				unlink_zone(t_block *zone, int index)
{
	t_block		*target;
	t_block		*head;
	t_block		*prev;
	int			count;

	target = zone;
	head = g_zone[index];
	prev = head;
	count = 0;
	while (head != NULL)
	{
		if (head != target)
			prev = head;
		else if (head == target)
			break ;
		count++;
		head = head->next;
	}
	return (unlink_this(zone, prev, index, count));
}

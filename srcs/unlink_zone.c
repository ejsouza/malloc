/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_zone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:47:22 by esouza            #+#    #+#             */
/*   Updated: 2020/02/18 15:47:27 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static size_t block_len(int index)
{
    t_block    *curr;
    size_t     len;

    curr = g_zone[index];
    len = 0;
    while (curr != NULL)
    {
        curr = curr->next;
        len++;
    }
    return (len);
}

static int  space_in_block(t_block *block, int index)
{
    size_t     min_left;

    min_left = index == 0 ? T_ZONE : S_ZONE;
    min_left += sizeof(t_chunk) * 2;
    if (block->blc_size > min_left)
        return (1);
    return (0);
}

static int unlink_this(t_block *target, t_block *prev, int index, size_t count)
{
    t_block *tmp;

    if (count == 0 && target == prev && index == TWO)
    {
        // The index here should be TWO cuz the others indexes always keeps at least one block
        if (target->next == NULL)
            g_zone[index] = NULL;
        else
            g_zone[index] = target->next;
    }
    else if (count == 0 && target == prev && block_len(index) > 1 && target->next != NULL)
    {
        if (!space_in_block(target->next, index))
            return (0);
        g_zone[index] = target->next;
        target = NULL;
    }
    else if (count == (block_len(index) - ONE)) // Shall be the last on the list
        prev->next = NULL;
    else
    {
        tmp = target->next;
        prev->next = tmp;
        target = NULL;
    }
    return (1);
}

int        unlink_zone(t_block *zone, int index)
{
    t_block *target;
    t_block *head;
    t_block *prev;
    int     count;

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
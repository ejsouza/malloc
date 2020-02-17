/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:52:12 by esouza            #+#    #+#             */
/*   Updated: 2020/02/11 10:52:16 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void     bzero_chunk(t_chunk *chunk)
{
    chunk->next = NULL;
    chunk->prev = NULL;
    chunk->free = 1;
}

static void     coalesce(t_chunk *curr, t_chunk *neighbor)
{
    t_chunk     *start;
    t_chunk     *tmp;

    start = NULL;
    if (curr < neighbor) // next
    {
        start = curr;
        if ((tmp = (t_chunk *)neighbor->next) != NULL)
            tmp->prev = start;
        start->free = 1;
        start->size += (neighbor->size + sizeof(t_chunk));
        start->next = (void *)tmp;
        bzero_chunk(neighbor);
    }
    else if (curr > neighbor) // prev
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

static void     free_ptr(t_chunk *ptr)
{
    t_chunk     *curr;
    t_block     *head_block;

    curr = ptr;
    curr->free = 1;
    while (curr->prev != NULL)
        curr = curr->prev;
    head_block = (t_block *)curr - ONE;
    head_block->blc_size += ptr->size + sizeof(t_chunk);
}

static int     neighbor_is_free(t_chunk *ptr)
{
    t_chunk    *prev;
    t_chunk    *curr;
    t_chunk    *next;
    int        flag;

    flag = 0;
    prev = ptr->prev;
    curr = ptr;
    next = (t_chunk *)ptr->next;

    if (next != NULL && next->free)
    {
        coalesce(curr, next);
        flag = 1;
        size_header_update(curr, next);
    }
    if (prev != NULL && prev->free)
    {
        coalesce(curr, prev);
        flag = 1;
        size_header_update(curr, prev);
    }
    return (flag);
}

void            ft_free(void *ptr)
{
    t_chunk     *curr;
    t_chunk     *next;
    t_chunk     *tmp;
    t_block     *block_head;
    size_t      size_ptr_to_free;
    
    if (ptr == NULL)
        return ;
    curr = (t_chunk *)ptr - ONE;
    next = curr;
    if (curr->free != 0)
        return ;
    size_ptr_to_free = curr->size;
    tmp = curr;
    while (tmp->prev != NULL)
        tmp = tmp->prev;
    if (!neighbor_is_free(curr))
        free_ptr(curr);
    while (next->next != NULL)
        next = (t_chunk *)next->next;
    block_head = (t_block *)tmp - ONE;
    if (next->size < block_head->blc_size)
        next->size = block_head->blc_size;
}

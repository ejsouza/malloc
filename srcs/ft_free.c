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

    // start = NULL;
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
    t_chunk     *tmp;
    t_block     *head_block;

    curr = ptr;
    tmp = curr;
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

    if (next != NULL && next->free && next->next != NULL)
    {
        coalesce(curr, next);
        flag = 1;
       // size_header_update(curr, next);
    }
    if (prev != NULL && prev->free)
    {
    //    printf("neighbor_is_free(2)\n");
        coalesce(curr, prev);
        flag = 1;
     //   size_header_update(curr, prev);
     //   size_header_update(prev, curr);
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
    
    curr = (t_chunk *)ptr - ONE;
    if (ptr == NULL || curr->free != 0)
        return ;
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

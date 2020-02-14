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
    // chunk->size = 0;
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
       // printf("coalesce(next) curr->size %zu | %zu\n", start->size, neighbor->size);
        start->next = (void *)tmp;
        bzero_chunk(neighbor);
    }
    else if (curr > neighbor) // prev
    {
        start = neighbor;
     //   printf("coalesce(prev) curr->size %zu | %zu | sizeof(t_chunk) %zu\n", start->size, neighbor->size, sizeof(t_chunk));
        if ((tmp = (t_chunk *)curr->next) != NULL)
            tmp->prev = start;
        start->free = 1;
        start->size += (curr->size + sizeof(t_chunk));
        start->next = (void *)tmp;
        bzero_chunk(curr);
    }
    // update_size_block_head(start);
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
   // printf("free_ptr(%zu)[%zu]\t head_block %zu\n", ptr->size, ptr->size - sizeof(t_chunk), head_block->blc_size);
    head_block->blc_size += ptr->size;
   // printf("free_ptr(%zu)[%zu]\t head_block %zu\n", ptr->size, ptr->size - sizeof(t_chunk), head_block->blc_size);
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
    t_chunk     *tmp;
    t_block     *block_head;
    size_t      size_ptr_to_free;
    
    printf("START FREE\n");
    if (ptr == NULL)
    {
        printf("NULL\n");
        printf("END FREE\n");
        return ;
    }
    curr = (t_chunk *)ptr - ONE;
    if (curr->free != 0)
    {
        printf("ERROR? %d\t SIZE %zu\n", curr->free, curr->size);
        printf("END FREE\n");
        return ;
    }
    size_ptr_to_free = curr->size;
    tmp = curr;
    while (tmp->prev != NULL)
    {
        tmp = tmp->prev;
    }
    if (!neighbor_is_free(curr))
    {
        printf("calling free_ptr(%p)\n", curr);
        free_ptr(curr);
    }
    /*
    ** Probably down here the test for freeing the BLOCK
    */
    //printf("MIDLE FREE\n");
 
    block_head = (t_block *)tmp - ONE;
    //printf("TOTO FREE\n");
    printf("%p size of block %zu\n", block_head, block_head->blc_size);
    //printf("TATA FREE\n");
    //free_block(block_head, size_ptr_to_free);
    printf("END FREE\n");
}

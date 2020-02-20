/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:51:56 by esouza            #+#    #+#             */
/*   Updated: 2020/02/11 10:52:02 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void show_alloc_mem(void)
{
    t_block *head;
    t_chunk  *chunk;
    int     index;
    printf("START SHOW_ALLO_MEM()\n");

    head = NULL;
    index = 0;
    while (index < NB_ZONE)
    {
        head = g_zone[index];
        printf("------------------------BLOCK HEAD {%p}-------------------------- index {%d}\n", head, index);
        while (head != NULL)
        {
            chunk = (void *)head + sizeof(t_block);
           int count = 0;
            printf("------------------------CHUNK {%p}-------------------------- index {%d}\n", chunk, index);
            while (chunk != NULL)
            {
               // printf("while(chunk != NULL) %p\n)", chunk);
                printf("%zu \t%p\t %p\t %zu\t %d\t%zu\t %d\n", (size_t)chunk, chunk, chunk->next, chunk->size, chunk->free, head->blc_size, ++count);
                chunk = (t_chunk *)chunk->next;
            }
            head = head->next;
        }
        index++;
    }
    printf("END SHOW_ALLO_MEM()\n");
}

static int  free_this_block(short index)
{
    t_block *head;
    t_chunk    *tmp;
    int     count_block;
    int     count_free;
    size_t  size_head;

    count_block = 0;
    count_free = 0;
    head = g_zone[index];
    if (index == 0)
    {
        size_head = (26 * getpagesize()) - sizeof(t_block) - sizeof(t_chunk);
        while (head != NULL)
        {
            if (head->blc_size >= T_ZONE && head->blc_size < size_head)
            {
           //     printf("FOUND A BLOCK WITH SPACE %p\n", head);
                count_free++;
            }
            count_block++;
            head = head->next;
        }
    }
    else if (index == 1)
    {
        size_head = (101 * getpagesize()) - sizeof(t_block) - sizeof(t_chunk);
        while (head != NULL)
        {
            if (head->blc_size >= S_ZONE && head->blc_size < size_head)
            {
         //       printf("FOUND A BLOCK WITH SPACE %p\n", head);
                count_free++;
            }
            count_block++;
            head = head->next;
        }
    }
    else // For the index == 2
    {
        tmp = (void *)head + sizeof(t_block);
        size_head = head->blc_size + tmp->size;
       // printf("size_head = %zu\n", size_head);
        while (head != NULL)
        {
            count_block++;
            head = head->next;
        }
        count_block = count_block < TWO ? TWO : count_block;
     //   printf("I'm here!!!!!!!!!!!!!!!!{%zu} addr head %p and addr tmp %p chunk->size %zu total blocks %d\n", size_head, head, tmp, tmp->size, count_block);
        return (1);
    }
    
   // printf("free_this_block? count_free %d count_block %d the return is %d\n", count_free, count_block, (count_block > 1 && count_free));
    return (count_block > 1 && count_free);
}

int         check_block_header(size_t size_head, size_t size_to_free)
{
    short   index;

    index = size_to_free <= T_ZONE ? 0 : 1;
    if (size_to_free > S_ZONE)
        return (free_this_block(TWO));
        //return (1);
    else if (index == 1 && size_head == ((101 * getpagesize()) - sizeof(t_chunk) - sizeof(t_block)))
    {
       // printf("FOUND in check_block_header() size_head %zu and size_to_free %zu index %d\n", size_head, size_to_free, index);
        return (free_this_block(index));
    }
    else if (index == 0 && size_head == ((26 * getpagesize()) - sizeof(t_chunk) - sizeof(t_block)))
    {
      // printf("Found a block completely freee\n");
        return (free_this_block(index));
    }
    return (0);
}

void        free_block(t_block *block_head, size_t size)
{
    int error;
    int size_block;
    int index;

    size_block = round_block(size);
    size_block++;
    index = size <= T_ZONE ? 0 : 1;
    error = 1;
    if (size > S_ZONE)
        index = 2;
    if (index == 2)
    {
        unlink_zone(block_head, index);
        error = munmap(block_head,  block_head->blc_size + sizeof(t_block) + sizeof(t_chunk));
        printf("THIS IS WHAT munmap() return %d\n", error);
    }
    else if (index == 1)
    {
        if (unlink_zone(block_head, index))
            error = munmap(block_head, 26 * getpagesize());
        printf("THIS IS WHAT munmap() return %d\n", error);
    }
    else if (index == 0)
    {
        if (unlink_zone(block_head, index))
            error = munmap(block_head, 26 * getpagesize());
        printf("THIS IS WHAT munmap() return %d\n", error);
    }
   // printf("---------------- in free block --------------- %zu\n", block_head->blc_size);
   //printf("%p \t %zu \t %zu\n", block_head, size - sizeof(t_chunk), block_head->blc_size);
}

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
    printf("START SHOW_ALLO_MEM()\n");

    head = g_zone[1];
   printf("------------------------BLOCK HEAD {%p}--------------------------\n", head);
    while (head != NULL)
    {
        chunk = (void *)head + sizeof(t_block);
        int count = 0;
       printf("------------------------CHUNK {%p}--------------------------\n", chunk);
        while (chunk != NULL)
        {
            printf("%zu \t%p\t %p\t %zu\t %d\t%zu\t %d\n", (size_t)chunk, chunk, chunk->next, chunk->size, chunk->free, head->blc_size, ++count);
            chunk = (t_chunk *)chunk->next;
        }
        head = head->next;
    }
    printf("END SHOW_ALLO_MEM()\n");
}

int         check_block_header(size_t size_head, size_t size_to_free)
{
    short   index;

    index = size_to_free <= T_ZONE ? 0 : 1;
    if (size_to_free > S_ZONE)
        index = 2;
    if (index == 2)
        return (1);
    else if (index == 1 && size_head == ((101 * getpagesize()) - sizeof(t_chunk) - sizeof(t_block)))
        printf("FOUND in check_block_header() size_head %zu and size_to_free %zu index %d\n", size_head, size_to_free, index);
    else if (index == 0 && size_head == ((26 * getpagesize()) - sizeof(t_chunk) - sizeof(t_block)))
        printf("Found a block completely freee\n");
    return (0);
}

void        free_block(t_block *block_head, size_t size)
{
    int error;
    int size_block;

    size_block = round_block(size);
    size_block++;
    if (size - sizeof(t_chunk) > S_ZONE)
    {
        error = munmap(block_head, size_block * getpagesize());
    }
    else if (size - sizeof(t_chunk) > T_ZONE && (block_head->blc_size + sizeof(t_block))
    == (size_t)PAGES_S)
    {
        printf("CALL FUNCTION TO CHECK IF THERE ONE MORE BLOCK BEFORE FREE BLOKC\n"); // handlle the SMALL (4096) blocks
    }
   // printf("---------------- in free block --------------- %zu\n", block_head->blc_size);
   printf("%p \t %zu \t %zu\n", block_head, size - sizeof(t_chunk), block_head->blc_size);
}

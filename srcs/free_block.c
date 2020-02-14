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

    head = g_zone[0];
    printf("------------------------BLOCK HEAD {%p}--------------------------\n", head);
    while (head != NULL)
    {
        chunk = (void *)head + sizeof(t_block);
        printf("------------------------CHUNK {%p}--------------------------\n", chunk);
        while (chunk != NULL)
        {
            printf("%zu \t%p\t %p\t %zu\t %d\t%zu\n", (size_t)chunk, chunk, chunk->next, chunk->size, chunk->free, head->blc_size);
            chunk = (t_chunk *)chunk->next;
        }
        head = head->next;
    }
    printf("END SHOW_ALLO_MEM()\n");
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

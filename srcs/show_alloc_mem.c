#include "../includes/malloc.h"
#include "../ft_printf/includes/libftprintf.h"

void show_alloc_mem(void)
{
    t_block *head;
    t_chunk  *chunk;
    int     index;
    ft_printf("START SHOW_ALLO_MEM()\n");

    head = NULL;
    index = 0;
    while (index < NB_ZONE)
    {
        head = g_zone[index];
        ft_printf("------------------------BLOCK HEAD {%p}-------------------------- index {%d}\n", head, index);
        while (head != NULL)
        {
            chunk = (void *)head + sizeof(t_block);
           int count = 0;
            ft_printf("------------------------ CHUNK {%p}-------------------------- index {%d}\n", chunk, index);
            while (chunk != NULL)
            {
                ft_printf("%zu \t%p\t %p\t %zu\t %d\t%zu\t %d\n", (size_t)chunk, chunk, chunk->next, chunk->size, chunk->free, head->blc_size, ++count);
                chunk = (t_chunk *)chunk->next;
            }
            head = head->next;
        }
        index++;
    }
    ft_printf("END SHOW_ALLO_MEM()\n");
}
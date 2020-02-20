#include "../includes/malloc.h"
#include "../ft_printf/includes/libftprintf.h"

static void print_block_name(int index, t_block *head)
{
    char *message[3];

    message[0] = "TINY : ";
    message[1] = "SMALL : ";
    message[2] = "LARGE : ";
    if (head != 0)
    {
        ft_putstr(message[index]);
        ft_printf("%p\n", head);
    }
}

static void print_chunk_info(t_chunk *chunk)
{
    uint64_t    addr;
    uint64_t    next;

    if (chunk == 0)
        return ;
    addr = (uint64_t)chunk;
    next = (uint64_t)chunk->next;
    number_to_hex(addr, 16);
    printf("\t %p\n", chunk);
   // printf("<< %llu >> %llu\n", addr, next);
}

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
        print_block_name(index, head);
     //   ft_printf("------------------------BLOCK HEAD {%p}-------------------------- index {%d}\n", head, index);
        while (head != NULL)
        {
            chunk = (void *)head + sizeof(t_block);
          // int count = 0;
       //     ft_printf("------------------------ CHUNK {%p}-------------------------- index {%d}\n", chunk, index);
            while (chunk != NULL)
            {
                print_chunk_info(chunk);
                //ft_printf("%zu \t%p\t %p\t %zu\t %d\t%zu\t %d\n", (size_t)chunk, chunk, chunk->next, chunk->size, chunk->free, head->blc_size, ++count);
                chunk = (t_chunk *)chunk->next;
            }
            head = head->next;
        }
        index++;
    }
    ft_printf("END SHOW_ALLO_MEM()\n");
}
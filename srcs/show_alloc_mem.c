/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:19:08 by esouza            #+#    #+#             */
/*   Updated: 2020/02/21 15:19:11 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void print_block_name(int index, t_block *head)
{
    char *message[3];

    message[0] = "TINY : ";
    message[1] = "SMALL : ";
    message[2] = "LARGE : ";
    uint64_t size_head;
    if (head != 0)
    {
        size_head = (uint64_t)head; 
        ft_putstr(message[index]);
        number_to_hex(size_head, 16);
        ft_putstr("\n");
    }
}

static void print_chunk_info(t_chunk *chunk)
{
    uint64_t    addr;
    uint64_t    next;
    size_t      size;

    if (chunk == 0)
        return ;
    addr = (uint64_t)chunk + sizeof(t_chunk);
    next = (uint64_t)chunk->next;
    size = chunk->size;
    number_to_hex(addr, 16);
    ft_putstr(" - ");
    number_to_hex(next, 16);
    ft_putstr(" : ");
    put_number(size);
    ft_putstr(" octets\n");
}

static void add_size(size_t *size, t_chunk *chunk)
{
    size_t      nb;

    nb = chunk->size;
    *size +=  chunk->size;
    print_chunk_info(chunk);
}

static void print_details(size_t *total_size)
{
    ft_putstr("Total : ");
    put_number((*total_size));
    ft_putstr(" octets\n");
}

void show_alloc_mem(void)
{
    t_block *head;
    t_chunk  *chunk;
    int     index;
    size_t  total_size;

    head = NULL;
    total_size = 0;
    index = -1;
    while (++index < NB_ZONE)
    {
        head = g_zone[index];
        print_block_name(index, head);
        while (head != NULL)
        {
            chunk = (void *)head + sizeof(t_block);
            while (chunk != NULL)
            {
                if (chunk->next != NULL && !chunk->free)
                    add_size(&total_size, chunk);
                chunk = (t_chunk *)chunk->next;
            }
            head = head->next;
        }
    }
    print_details(&total_size);
}

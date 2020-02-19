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

static void unlink_this(t_block *zone, size_t count, size_t to_free, int index)
{
    t_block *curr;
    t_block *tmp;

    curr = zone;
    printf("In unlink_this() g_zone[index] %p\n", g_zone[index]);
    if (to_free == 0)
    {
        tmp = curr->next;
        g_zone[index] = tmp;
        printf("In unlink_this() after change g_zone[index] %p\n", g_zone[index]);
    }
    else if (count == 0 && to_free == 0)
        ;

}

void        unlink_zone(t_block *zone, int index)
{
    t_block *head;
    t_block *tmp;
    size_t  count_blocks;
    size_t  the_one_to_free;
    size_t  block_len;

    count_blocks = 0;
    the_one_to_free = 0;
    printf("Enter unlink_zone(%p)\n", zone);
    head = zone;
    tmp = zone;
    block_len = 0;
    printf("unlink_zone() zone %p, head %p, tmp %p THE NEXT %p\n", zone, head, tmp, tmp->next);
    while (tmp != NULL)
    {
        block_len++;
        tmp = tmp->next;
    }
    printf("in unlink_zone() the number of blocks are %zu\n", block_len);
    while (head != NULL)
    {
        if (head == zone)
        {
            the_one_to_free = count_blocks;
            printf("head(%p) and zone(%p) points to the same address\n", head, zone);
            printf("head->next ? %p\n", head->next);
        }
        else
            printf("head(%p) and zone(%p) doesn't points to the same address\n", head, zone);
        printf("This is the address of zone %p and have size of %zu\n", head, head->blc_size);
        head = head->next;
        count_blocks++;
    }
    printf("the count_blocks should be the number of blocks %zu \t the_one_to_free %zu\n", count_blocks, the_one_to_free);
    unlink_this(zone, count_blocks, the_one_to_free, index);
    printf("There are %zu total blocks and the block position to free %zu\n", count_blocks, the_one_to_free);
}
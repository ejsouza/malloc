/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_zone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:18:23 by esouza            #+#    #+#             */
/*   Updated: 2019/11/08 17:23:03 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		initialize_zone(t_block *zone, int size_zone)
{
	zone->next = NULL;
	zone->block_size = size_zone;
	zone->start = zone + sizeof(t_block) / sizeof(t_block);
}

t_block			*malloc_zone(short index)
{
	t_block		*zone;
	size_t		size_zone;
	size_t		number_page;
	size_t		page_size;

	size_zone = index == 0 ? T_ZONE : S_ZONE;
	page_size = getpagesize();
	number_page = page_size / size_zone;
	number_page = MIN_ALLOC / number_page;
	number_page++;
	printf(">>>>>>>>>>>>>> %zu\t>>> %zu\n", number_page, number_page * page_size);
	zone = (t_block *)mmap(NULL, number_page * page_size, PROT_READ
				| PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (zone != MAP_FAILED && zone != NULL)
		initialize_zone(zone, number_page * page_size);
	return (zone);
}

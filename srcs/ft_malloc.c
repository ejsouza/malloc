/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:52:24 by esouza            #+#    #+#             */
/*   Updated: 2020/02/11 10:52:29 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static short	zone_size(size_t size)
{
	if (size <= T_ZONE)
		return (TINY);
	else if (size <= S_ZONE)
		return (SMALL);
	return (LARGE);
}


void		*malloc(size_t size)
{
	void	*addr;
	short	index;

//	ft_putstr("\nEnter malloc\n");
	if (size < 0)
		return (NULL);
	if (size % TWO)
		size++;
	index = zone_size(size);
	addr = alloc_handler(size, index);
	//printf("%p\n", addr);
//	ft_putstr("Exit malloc\n\n");
	//ft_putstr("\n\n");
	//show_alloc_mem();
	//ft_putstr("\n\n");

	/* delete bellow */
	//uint64_t toto = (uint64_t)addr;
	//ft_putstr("The pointer returned by malloc()\n");
	//number_to_hex(toto, 16);
	printf("\n");
	return (addr);
}

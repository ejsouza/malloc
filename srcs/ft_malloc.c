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

short	zone_size(size_t size)
{
	if (size <= T_ZONE)
		return (TINY);
	else if (size <= S_ZONE)
		return (SMALL);
	return (LARGE);
}


void		*malloc(size_t size)
{
	// ft_putstr("Enter malloc()\n");
	void	*addr;
	short	index;

	printf("in malloc with size %zu\n", size);
	if (size == 0 || size > SIZE_MAX_GUARD) 
	{	
		return (NULL);
	}
	//if (size == 0)
	//	size = MIN_SIZE_ALLOC;
	/*
	** If size is not a multiply of 16;
	** Set it to the closest multiply of 16 past it;
	*/
	// ft_putstr("size before bitwise shift ");
	// put_number(size);
	// ft_putstr("\n");
	size = (size + 15) & ~15;
	// ft_putstr("size after bitwise shift ");
	// put_number(size);
	// ft_putstr("\n");
	index = zone_size(size);
	addr = alloc_handler(size, index);
	// ft_putstr("Exit malloc()\n");
	printf("exit malloc with the size %zu\n", size);
	return (addr);
}

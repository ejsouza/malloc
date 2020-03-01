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
	void	*addr;
	short	index;

	ft_putstr("malloc(mine)\n");
	if (size < 0)
		return (NULL);
	if (size == 0)
		size = MIN_SIZE_ALLOC;
	size = (size + 15) & ~15;
	index = zone_size(size);
	addr = alloc_handler(size, index);
	return (addr);
}

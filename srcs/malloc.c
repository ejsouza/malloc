/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:10:35 by esouza            #+#    #+#             */
/*   Updated: 2020/03/09 13:29:49 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

short			zone_size(size_t size)
{
	if (size <= T_ZONE)
		return (TINY);
	else if (size <= S_ZONE)
		return (SMALL);
	return (LARGE);
}

int				int_len(int nb)
{
	int			i;

	i = 0;
	if (nb <= i)
		i = (i < 0) ? 2 : 1;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static void		*malloc_twin(size_t size)
{
	void		*addr;
	int			index;

	addr = NULL;
	if (size <= S_ZONE)
		size = (size + 15) & ~15;
	else
		size = (size + 511) & ~511;
	if (size == 0 || size > 1844674407370955161)
		size = 16;
	index = zone_size(size);
	addr = alloc_handler(size, index);
	write_to_file(addr, size);
	return (addr);
}

/*
** ATTENTION: do NOT forget to uncomment line 53.
** This line was comment just for the purpose of the tests.
** This line makes my project NON norm.
*/

void			*malloc(size_t size)
{
	void		*addr;

	pthread_mutex_lock(&g_mutex);
	addr = malloc_twin(size);
	pthread_mutex_unlock(&g_mutex);
	return (addr);
}

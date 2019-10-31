/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mblock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:39:03 by esouza            #+#    #+#             */
/*   Updated: 2019/10/31 16:34:36 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static size_t			define_bins_size(size_t size)
{
	if (size <= TINY)
		return ((size_t)TINY);
	else if (size <= SMALL)
		return ((size_t)SMALL);
	return (size);
}

void				*get_mblock(size_t size, t_block *head)
{
	void			*addr;

	addr = mmap(NULL, define_bins_size(size), PROT_READ | PROT_WRITE, MAP_ANON
			| MAP_PRIVATE, -1, 0);
	if (addr != MAP_FAILED)
		head->mmap_calls++;
	return (addr);
}

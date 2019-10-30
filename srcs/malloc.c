/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:18:54 by esouza            #+#    #+#             */
/*   Updated: 2019/10/30 10:38:50 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void						*malloc(size_t size)
{
	void		*addr;
	if (size == 0)
		return (NULL);
	if ((addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE
					, -1, 0)) == MAP_FAILED)
	{
		printf("mmap failed %d\n", (int)addr);
		return (NULL);	
	}
	return (addr);
}


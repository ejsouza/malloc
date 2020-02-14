/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:18:54 by esouza            #+#    #+#             */
/*   Updated: 2019/11/08 17:16:48 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block						*zone[NB_ZONE];

void						*malloc(size_t size)
{
	void			*addr;
	printf("t_block = %lu\n", sizeof(t_block));
	if ((addr = handler_request(size, &zone[NB_ZONE])) == MAP_FAILED)
		return (NULL);
	printf("********* %d\n", zone_size(size));
	return (addr);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:18:54 by esouza            #+#    #+#             */
/*   Updated: 2019/11/05 16:58:09 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block						*zone[NB_ZONE];

void						*malloc(size_t size)
{
	void			*addr;

	if ((addr = handler_request(size, zone)) == MAP_FAILED)
		return (NULL);
	return (addr);
}


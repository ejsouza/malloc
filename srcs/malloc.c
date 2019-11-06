/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:18:54 by esouza            #+#    #+#             */
/*   Updated: 2019/11/06 13:25:32 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block						*zone[NB_ZONE];

void						*malloc(size_t size)
{
	void			*addr;

	if ((addr = handler_request(size, &zone[NB_ZONE])) == MAP_FAILED)
		return (NULL);
	return (addr);
}


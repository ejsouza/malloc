/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:18:54 by esouza            #+#    #+#             */
/*   Updated: 2019/10/31 16:02:54 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block						head;

void						*malloc(size_t size)
{
	void					*addr;
// check shall be made in this way, malloc returns a page for size = 0
	if (size < 0)
		return (NULL);
	if ((addr = request_handler(size, &head)) == NULL || addr == MAP_FAILED)
		return (NULL);
	return (addr);
}


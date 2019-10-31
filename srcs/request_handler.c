/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:07:36 by esouza            #+#    #+#             */
/*   Updated: 2019/10/31 16:03:18 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void					*request_handler(size_t size, t_block *head)
{
	void				*addr;

	addr = NULL;
	if (head->mmap_calls == 0)
	{
		addr = get_mblock(size);
	}
	return (addr);
}

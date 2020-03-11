/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:11:04 by esouza            #+#    #+#             */
/*   Updated: 2020/03/10 09:24:30 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		*malloc_min_size(void *ptr)
{
	void		*new_chunk;

	new_chunk = malloc(MIN_SIZE_ALLOC);
	if (!new_chunk)
		return (ptr);
	free(ptr);
	return (new_chunk);
}

int				size_what_index(size_t size, int index)
{
	if (index == TINY && size > T_ZONE)
		return (ONE);
	else if (index == SMALL && size > S_ZONE)
		return (ONE);
	else if (index == LARGE)
		return (ONE);
	return (0);
}

int				same_index(size_t size, size_t curr_size)
{
	int			curr_index;

	if (curr_size <= T_ZONE)
		curr_index = 0;
	else if (curr_size <= S_ZONE)
		curr_index = 1;
	else
		return (1);
	if (curr_index == 0 && size > T_ZONE)
		return (0);
	else if (curr_index == 1 && size > S_ZONE)
		return (0);
	return (1);
}

/*
** A call to realloc with a NULL ptr and size > 0 is equal to calling
** malloc(size)
*/

static void		*reall_twin(void *ptr, size_t size)
{
	int			index;
	void		*addr;

	addr = NULL;
	if (!is_pointer_valid(ptr))
	{
		if (ptr)
			return (NULL);
		if (size > 0)
		{
			size = (size + 15) & ~15;
			return (malloc(size));
		}
	}
	if (size == 0)
		return (malloc_min_size(ptr));
	if (size <= T_ZONE)
		size = (size + 15) & ~15;
	else
		size = (size + 511) & ~511;
	index = zone_size(size);
	addr = realloc_handler(ptr, size, index);
	return (addr);
}

void			*realloc(void *ptr, size_t size)
{
	void		*addr;

	pthread_mutex_lock(&g_mutex);
	addr = reall_twin(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (addr);
}

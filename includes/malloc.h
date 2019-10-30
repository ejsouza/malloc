/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:24:40 by esouza            #+#    #+#             */
/*   Updated: 2019/10/30 11:49:02 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/types.h>
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>
# include <pthread.h>
# include <stddef.h>
#include <stdio.h> //to be deleted

# define TINY			1028 * 4096
# define SMALL			4096 * 4096

typedef struct			s_chunk
{
	size_t				chunk_size;
	_Bool				free;
	struct s_chunkc		*next;
	struct s_chunk		*previous;
}						t_chunk;

typedef struct			s_block
{
	size_t				block_size;
	void				*data;
	struct s_block		*next;
	struct s_block		*previous;
}						t_block;


void 					*malloc(size_t size);
void 					*realloc(void *ptr, size_t size);
void					free(void *ptr);
void 					show_alloc_mem(void);

size_t					ft_strlen(const char *s);
void					ft_putstr(char *str);

#endif

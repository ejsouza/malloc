/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:24:40 by esouza            #+#    #+#             */
/*   Updated: 2019/11/06 14:51:42 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/types.h>
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>
# include <pthread.h>
//# include <stddef.h>
#include <stdio.h> //to be deleted

# define TINY			0
# define SMALL			1
# define LARGE			2
# define MIN_ALLOC		100
# define NB_ZONE		3
# define T_ZONE			1028
# define S_ZONE			4096

typedef struct			s_chunk
{
	size_t				chunk_size;
	_Bool				free;
	struct s_chunkc		*next;
	struct s_chunk		*previous;
}						t_chunk;

typedef struct			s_block
{
	struct s_block		*start;
	struct s_block		*next;
	size_t				block_size;
}						t_block;


void 					*malloc(size_t size);
void 					*realloc(void *ptr, size_t size);
void					free(void *ptr);
void 					show_alloc_mem(void);

void					*handler_request(size_t size, t_block *zone[NB_ZONE]);


size_t					ft_strlen(const char *s);
void					ft_putstr(char *str);

#endif

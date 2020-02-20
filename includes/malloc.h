#ifndef MALLOC_H
# define MALLOC_H

# include <sys/types.h>
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>
# include <pthread.h>
#include <stdio.h> //to be deleted


# define ONE			1
# define TWO			2
# define TINY			0
# define SMALL			1
# define LARGE			2
# define NB_ZONE		3
# define MIN_ALLOC		100
# define T_ZONE			1024
# define S_ZONE			4096

# define PAGES_T		(getpagesize() * 26)
# define PAGES_S		(getpagesize() * 101)

typedef struct			s_chunk
{
	struct s_chunkc		*next;
	struct s_chunk		*prev;
	size_t				size;
	_Bool				free;
}						t_chunk;

typedef struct			s_block
{
	struct s_block		*next;
	size_t				blc_size;
}				t_block;

t_block				*g_zone[NB_ZONE];

void				*ft_malloc(size_t size); // clean the ft_ from the function name
void				ft_free(void *ptr);		// Dito
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);

void				*alloc_handler(size_t size, short inde);
void				*link_zones(t_block *new_zone, size_t size
		, short index);
int					unlink_zone(t_block *zone, int index);
void				*find_free_space(size_t size, short index);
void				init_chunk(t_chunk **chunk, size_t size);
// void				*init_chunk_header(t_chunk **chunk, size_t size);
void				update_size_block_head(t_chunk *start); // not in use
// void				size_header_update(t_chunk *curr);
void				free_block(t_block *block_head, size_t size);
int         		check_block_header(size_t size_head, size_t size_to_free);
void				*split_chunk(t_chunk *chunk, size_t size);
void    			*split_to_middle(t_chunk *curr, size_t size);
size_t				round_block(size_t size);


size_t				ft_strlen_malloc(const char *s);
void				ft_putstr_malloc(char *str);

#endif

#include "../includes/malloc.h"

void        *split_chunk(t_chunk *chunk, size_t size)
{
    t_chunk     *curr;
    t_chunk     *new_chunk;
    size_t      total_size;
    
    curr = chunk;
    total_size = curr->size;
    new_chunk = (void *)curr + (size + sizeof(t_chunk));
    curr->next = (void *)new_chunk;
    curr->free = 0;
    curr->size = size;
    new_chunk->next = NULL;
    new_chunk->prev = curr;
    new_chunk->size = ((total_size - size) - sizeof(t_chunk));
    new_chunk->free = 1;
    return (curr + ONE);
}

void    *split_to_middle(t_chunk *curr, size_t size)
{
    t_chunk     *new_chunk;
    void        *tmp;

    tmp = (void *)curr + size + sizeof(t_chunk);
    new_chunk = tmp;
    new_chunk->size = curr->size - (size + sizeof(t_chunk));
    new_chunk->free = 1;
    new_chunk->prev = curr;
    new_chunk->next = curr->next;
    curr->next = (void *)new_chunk;
    curr->free = 0;
    curr->size = size;
    return (curr + ONE);
}
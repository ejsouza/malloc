#include "../includes/malloc.h"

void        *split_chunk(t_chunk *chunk, size_t size)
{
    printf("in split_chunk(chunk %zu size %zu)\n", chunk->size, size);
    t_chunk    *next;
    t_chunk     *curr;
    t_chunk     *new_chunk;
    size_t      total_size;
    
    curr = chunk;
    next = (void *)curr->next;
    total_size = curr->size;
    new_chunk = (void *)curr + (size + sizeof(t_chunk));
    curr->next = (void *)new_chunk;
    curr->free = 0;
    curr->size = size;
    next->prev = new_chunk;
    new_chunk->next = (void *)next;
    new_chunk->prev = curr;
    new_chunk->size = ((total_size - size) - sizeof(t_chunk));
    new_chunk->free = 1;
    return (curr + ONE);
}
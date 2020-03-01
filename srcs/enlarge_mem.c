#include "../includes/malloc.h"

static void *merge_create(t_chunk *start, t_chunk *next, size_t size)
{
    t_chunk *new_chunk;
    t_chunk *third_chunk;
    t_block *head;
    void    *tmp;
    size_t  total_size;

    tmp  = (void *)start + size + sizeof(t_chunk);
    new_chunk = tmp;
    third_chunk = (t_chunk *)next->next;
    total_size = start->size + next->size;
    new_chunk->free = 1;
    new_chunk->size = total_size - size;
    new_chunk->next = (void *)third_chunk;
    /*
    ** total_size here is reset because I lose the value of the start->size once I set it to size
    ** and I need the inicial value from start->size to update the block-blc_size;
    */
    total_size = start->size;
    new_chunk->prev = start;
    if (third_chunk != NULL)
        third_chunk->prev = new_chunk;
    start->next = (void *)new_chunk;
    start->size = size;
    while (new_chunk->prev)
        new_chunk = new_chunk->prev;
    head = (void *)new_chunk - sizeof(t_block);
    head->blc_size -= size - total_size;
    return (start + ONE);
}

static void *merge_next_chunk(t_chunk *start, t_chunk *next, size_t size, int times)
{
    void    *addr;
    t_chunk *third_chunk;
    t_chunk *curr;
    t_block *head;

    addr = NULL;
    curr = start;
    if ((start->size + next->size) == size)
    {
        ft_putstr("THEY ARE THE SAME\n");
        third_chunk = (t_chunk *)next->next;
        start->size += next->size + sizeof(t_chunk); // next->size + sizeof(t_chunk) - blc_size
        start->next = (void *)third_chunk;
        if (third_chunk)
            third_chunk->prev = start;
        addr = (void *)start + sizeof(t_chunk);
        while (curr->prev)
            curr = curr->prev;
        head = (void *)curr - sizeof(t_block);
        head->blc_size -= (next->size + sizeof(t_chunk));
    }
    if ((start->size + next->size) > (size + (sizeof(t_chunk) + MIN_SIZE_ALLOC * times)))
        addr = merge_create(start, next, size);
    return (addr);
}

void        *enlarge_mem(t_chunk *start, t_chunk *next, size_t size, int times)
{
    void    *addr;
    void    *ptr;

    addr = NULL;
    ptr = (void *)start + sizeof(t_chunk);
    if (!next)
    {
        if ((addr = malloc(size)) == NULL)
            return (start + ONE);
        ft_memmove(addr, ptr, start->size);
    }
    else if (next->free && (start->size + next->size) >= size)
    {
        addr = merge_next_chunk(start, next, size, times);
    }
    else
    {
       // put_number(next->free);
        if ((addr = malloc(size)) == NULL)
            return (start + ONE);
        ft_memmove(addr, ptr, start->size);
    }
    return (addr);
}
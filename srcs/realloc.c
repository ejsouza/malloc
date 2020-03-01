#include "../includes/malloc.h"

static void     *malloc_min_size(void *ptr)
{
    void        *new_chunk;

    new_chunk = malloc(MIN_SIZE_ALLOC);
    if (!new_chunk)
        return (ptr);
    free(ptr);
    return (new_chunk);
}

// static void *merge_next_chunks(t_chunk *start, size_t size)
// {
//     /* Returns pointer to user and not a chunk head */
//     t_chunk *curr;
//     t_chunk *next;
//     t_chunk *third_chunk;
//     size_t  total_size;

//     curr = start;
//     next = start->next;
//     third_chunk = next->next;
//     total_size = next->size + sizeof(t_chunk);
//     next->free = 0;
// }

static void *split_create_new(t_chunk *start, size_t size)
{
    t_chunk *next;
    t_chunk *new_chunk;
    void    *tmp;
    size_t  total_size;
    t_block     *head;

    next = (t_chunk *)start->next;
    total_size = (start->size - size) - sizeof(t_chunk);
    tmp = (void *)start + size + sizeof(t_chunk);
    new_chunk = tmp;
    new_chunk->free = 1;
    new_chunk->size = total_size;
    new_chunk->next = (void *)next;
    new_chunk->prev = start;
    if (next != NULL)
        next->prev = new_chunk;
    start->next = (void *)new_chunk;
    start->size = size;
    while (next->prev)
        next = next->prev;
    head = (void *)next - sizeof(t_block);
    head->blc_size += total_size;
    return (start + ONE);
}

static void *realloc_handler(void *ptr, size_t size, int index)
{
    void    *tmp;
    void    *addr;
    t_chunk *curr;
    t_chunk *next;
    int     times;

    times = (index == 0) ? 1 : 32;
    tmp = ptr - sizeof(t_chunk);
    curr = (t_chunk *)tmp;
    next = (t_chunk *)curr->next;
    addr = NULL;
    if (size <= curr->size)
    {
        /* There is not enough space left to create a new_chunk, so just add them together */
        if ((curr->size - size) > (sizeof(t_chunk) + (MIN_SIZE_ALLOC * times)))
            addr = split_create_new(curr, size);
        else
            return (ptr);
    }
    else
    {
        printf("Not handled\n");
    }
    
    return (addr);
}

void   *realloc(void *ptr, size_t size)
{
    void    *addr;
    int     index;

    addr = NULL;
    if (!is_pointer_valid(ptr))
        return (NULL);
    if (size == 0)
        return (malloc_min_size(ptr));
    size = (size + 15) & ~15;
    index = zone_size(size);
    addr = realloc_handler(ptr, size, index);
    
    return (addr);
}
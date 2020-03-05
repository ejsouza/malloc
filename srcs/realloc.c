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

static int  size_what_index(size_t size, int index)
{
    if (index == TINY && size > T_ZONE)
        return (ONE);
    else if (index == SMALL && size > S_ZONE)
        return (ONE);
    else if (index == LARGE)
        return (ONE);
    return (0);
}

static int  same_index(size_t size, size_t curr_size)
{
    int     curr_index;
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
    if (size_what_index(size, curr->size))
    {
        if ((addr = malloc(size)) == NULL)
            return (ptr);
        ft_memmove(addr, ptr, curr->size);
        free(ptr);
    }
    else if (size <= curr->size && same_index(size, curr->size))
    {
        /* There is not enough space left to create a new_chunk, so just add them together */
        if ((curr->size - size) > (sizeof(t_chunk) + (MIN_SIZE_ALLOC * times)))
            addr = split_create_new(curr, size);
        else
            return (ptr);
    }
    else
        addr = enlarge_mem(curr, next, size, times);
    return (addr);
}

static void *reall_twin(void *ptr, size_t size)
{
    int     index;
    void    *addr;

    addr = NULL;
    if (size > SIZE_MAX_GUARD)
        return (NULL);
    if (!is_pointer_valid(ptr))
    {
        /*
        ** A call to realloc with a NULL ptr and size > 0 is equal to calling malloc(size)
        */
        if (size > 0)
        {
            size = (size + 15) & ~15;
            return (malloc(size));
        }
        return (NULL);
    }
    if (size == 0)
        return (malloc_min_size(ptr));
    size = (size + 15) & ~15;
    index = zone_size(size);
    addr = realloc_handler(ptr, size, index);
    return (addr);
}

void   *realloc(void *ptr, size_t size)
{
    void    *addr;

    pthread_mutex_lock(&g_mutex);
    addr = NULL;
    addr = reall_twin(ptr, size);
    pthread_mutex_unlock(&g_mutex);
    return (addr);
}
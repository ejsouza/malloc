#include "../includes/malloc.h"

static void     *merge_end(t_chunk *chunk, t_chunk *last, size_t size, size_t size_head)
{
    t_chunk     *set_to_null;
    t_chunk     *curr;
    t_chunk     *new_chunk;
    t_block     *head;
   // void        *tmp;

    if (size)
        ;
    set_to_null = (t_chunk *)chunk->next;
    curr = chunk;
    new_chunk = (void *)chunk + sizeof(t_chunk) + size_head;
    new_chunk->free = 1;
    new_chunk->size = last->size - sizeof(t_chunk) - size_head;
    new_chunk->next = NULL;
    new_chunk->prev = chunk; 
    chunk->size = size_head;
    chunk->next = (void *)new_chunk;
    while (curr != NULL)
        curr = curr->prev;
    head = (void *)curr - sizeof(t_block);
    printf("head %p and head->size %zu\n", head, head->blc_size);
    if (chunk == NULL)
        return (NULL);
    return (chunk + ONE);

}

static void    *merge_chunk(t_chunk *chunk, t_chunk *next, size_t size)
{
    t_chunk     *curr;
    t_chunk     *tmp;
    size_t      size_found;
    size_t      count;

    curr = chunk;
    tmp = next;
    size_found = chunk->size;
    count = 0;
    while (curr->next != NULL && tmp->free && size_found < size)
    {
        printf("one\n");
        tmp = (t_chunk *)curr->next;
        printf("two\n");
        size_found += tmp->size;
        count++;
        printf("three %zu\n", size_found);
        if (size_found >= size && tmp->next != NULL)
        {
            tmp = (t_chunk *)tmp->next;
            chunk->next = (void *)tmp;
            chunk->size = size_found;
            tmp->prev = (t_chunk *)chunk;
            return (chunk + ONE);
        }
        else if (size_found >= size && tmp->next == NULL)
        {
            printf("handlle here \n");
            merge_end(chunk, tmp, size, size_found);
        }
    }
    printf("merge_chunk(3) count %zu\n", count);
    return (NULL);
}

static void *extend_ptr(void *ptr, size_t size)
{
    void    *tmp;
    t_chunk *chunk;
    t_chunk *new_chunk;
    t_chunk *next;

    new_chunk = NULL;
    tmp = ptr - (sizeof(t_chunk));
    chunk = tmp;
    next = (t_chunk *)chunk->next;
    if (next != NULL && next->free)
        if ((new_chunk = merge_chunk(chunk, next, size)) == NULL)
            new_chunk = ft_malloc(size);
    if (new_chunk == NULL)
        return (NULL);
    ft_memmove(new_chunk, ptr, size);
    return (new_chunk);
}

 void   *ft_realloc(void *ptr, size_t size)
 {
     /*
     ** The realloc() function tries to change the size of the allocation pointed to by ptr to size,
     ** and returns ptr.
     ** If there is not enough room to enlarge the memory allocation pointed to by ptr,
     ** realloc() creates a new allocation,
     ** copies as much of the old data pointed to by ptr as will fit to the new allocation,
     ** frees the old allocation, and returns a pointer to the allocated memory.
     ** If ptr is NULL, realloc() is identical to a call to malloc() for size bytes.
     ** If size is zero and ptr is not NULL,
     ** a new, minimum sized object is allocated and the original object is freed.
     ** 
     */
    void    *tmp;
    t_chunk *chunk;
    t_chunk *new_chunk;

    if (!is_pointer_valid(ptr))
        return (NULL);
    tmp = ptr - (sizeof(t_chunk));
    chunk = tmp;
    if (size <= chunk->size || size == 0)
    {
        if ((new_chunk = ft_malloc(size)) == NULL)
            return (NULL);
        ft_memmove(new_chunk, ptr, size);
        ft_free(ptr);
        return (new_chunk);
    }
    else if (size > chunk->size)
    {
        if ((new_chunk = extend_ptr(ptr, size)) == NULL)
            return (NULL);
        ft_memmove(new_chunk, ptr, size);
        ft_free(ptr);
    }
    printf("ptr %p chunk %p chunk->size %zu size %zu\n", ptr, chunk, chunk->size, size);
    return (NULL);
 }
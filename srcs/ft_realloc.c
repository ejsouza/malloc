/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 13:17:14 by esouza            #+#    #+#             */
/*   Updated: 2020/02/25 13:17:19 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void     *merge_end(t_chunk *chunk, t_chunk *last, size_t size, size_t size_found)
{
    // t_chunk     *set_to_null;
    // t_chunk     *curr;
    t_chunk     *new_chunk;
    // t_block     *head;
    void        *tmp;

    if (size == size_found)
    {
        /* Here I add the sizeof(t_chunk) to size because there's no more space left to create another chunk */
        chunk->size = size + sizeof(t_chunk);
        chunk->next = NULL;
        last = NULL;
        return (chunk + ONE); 
    }
    else if (size_found > size && (size_found - (size + sizeof(t_chunk))) > MIN_SIZE_ALLOC)
    {
        printf("BEFORE ALL chunk->free %d chunk->size %zu\n", chunk->free, chunk->size);
        tmp = (void *)chunk + size;
        printf("chunk %p tmp %p tmp + sizeof %p\n", chunk, tmp, tmp + sizeof(t_chunk));
        new_chunk = (t_chunk *)tmp;
        new_chunk->free = 1;
        new_chunk->size = ((size_found - size) - sizeof(t_chunk));
        printf("size_found %zu size %zu sizeof(chunk) %zu\n", size_found, size, sizeof(t_chunk));
        printf("size_found %zu \t new_chunk->size %zu\n", size_found, new_chunk->size);
        new_chunk->next = NULL;
        new_chunk->prev = chunk;
        chunk->next = (void *)new_chunk;
        chunk->size = size;
        printf("leaves merge_end(%p) chunk + ONE %p\n", chunk, chunk + ONE);
        printf("chunk->free %d \t chunk->size %zu\n", chunk->free, chunk->size);

        return (chunk + ONE);
    }
    // if (size)
    //     ;
    // set_to_null = (t_chunk *)chunk->next;
    // curr = chunk;
    // new_chunk = (void *)chunk + sizeof(t_chunk) + size_head;
    // new_chunk->free = 1;
    // new_chunk->size = last->size - sizeof(t_chunk) - size_head;
    // new_chunk->next = NULL;
    // new_chunk->prev = chunk; 
    // chunk->size = size_head;
    // chunk->next = (void *)new_chunk;
    // while (curr != NULL)
    //     curr = curr->prev;
    // head = (void *)curr - sizeof(t_block);
    // printf("head %p and head->size %zu\n", head, head->blc_size);
    // if (chunk == NULL)
    //     return (NULL);
    // return (chunk + ONE);
    return (NULL);
}

static void    *merge_chunk(t_chunk *chunk, t_chunk *next, size_t size)
{
    t_chunk     *curr;
    t_chunk     *tmp;
    size_t      size_found;

    curr = chunk;
    tmp = next;
    size_found = chunk->size;
    while (curr->next != NULL && tmp->free && size_found < size)
    {
        tmp = (t_chunk *)curr->next;
        size_found += tmp->size;
        if (size_found >= size && tmp->next != NULL)
        {
            tmp = (t_chunk *)tmp->next;
            chunk->next = (void *)tmp;
            chunk->size = size_found;
            tmp->prev = (t_chunk *)chunk;
            return (chunk + ONE);
        }
        else if (size_found >= size && tmp->next == NULL)
            return (merge_end(chunk, tmp, size, size_found));
    }
    return (NULL);
}

static void *extend_ptr(void *ptr, size_t size)
{
    void    *tmp;
    t_chunk *chunk;
    void    *new_chunk;
    t_chunk *next;

    new_chunk = NULL;
    tmp = ptr - (sizeof(t_chunk));
    chunk = tmp;
    next = (t_chunk *)chunk->next;
    if (next != NULL && next->free)
        if ((new_chunk = merge_chunk(chunk, next, size)) == NULL)
        {
            printf("merge_chunk(%p)\n", new_chunk);
            new_chunk = ft_malloc(size);
        }
    if (new_chunk == NULL)
        return (ptr);
    ft_memmove(new_chunk, ptr, size);
    printf("LEAVES extend_ptr(%s)\n", new_chunk);
    return (new_chunk);
}

static void *malloc_new(void *ptr, size_t size)
{
    void        *new_chunk;

    if ((new_chunk = ft_malloc(size)) == NULL)
        return (ptr);
    ft_memmove(new_chunk, ptr, size);
    ft_free(ptr);
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
    void    *new_chunk;

    if (!is_pointer_valid(ptr))
        return (NULL);
    tmp = ptr - (sizeof(t_chunk));
    chunk = tmp;
    new_chunk = NULL;
    if (size % 2)
        size = malloc_base_16(size);
    if (size == 0)
    {
        return (malloc_new(ptr, MIN_SIZE_ALLOC));
        //if ((new_chunk = ft_malloc(MIN_SIZE_ALLOC)) == NULL)
        //    return (NULL);
        //ft_memmove(new_chunk, ptr, MIN_SIZE_ALLOC);
        //ft_free(ptr);
        //return(new_chunk);
    }
    else if (size <= chunk->size)
    {
        return (malloc_new(ptr, size));
        //if ((new_chunk = ft_malloc(size)) == NULL)
        //    return (NULL);
        //ft_memmove(new_chunk, ptr, size);
        //ft_free(ptr);
        //return (new_chunk);
    }
    else if (size > chunk->size)
    { 
        if ((new_chunk = extend_ptr(ptr, size)) == NULL)
            return (NULL);
        ft_memmove(new_chunk, ptr, size);
        ft_free(ptr);
        return (new_chunk);
    }
    printf("ptr %p chunk %p chunk->size %zu size %zu\n", ptr, chunk, chunk->size, size);
    return (NULL);
 }

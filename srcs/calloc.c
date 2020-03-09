/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:09:14 by esouza            #+#    #+#             */
/*   Updated: 2020/03/09 10:09:20 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void *calloc_twin(size_t count, size_t size)
{
    size_t   request_size;
    void *ptr;    

    ptr = NULL;
    if (count == 0 || size == 0)
        return (NULL);
    else if (count > SIZE_MAX_GUARD || size > SIZE_MAX_GUARD)
        return (NULL);
    request_size = count * size;
    if ((ptr = malloc(request_size)) == NULL)
        return (NULL);
    ft_bzero(ptr, request_size);
    return (ptr);
}

void        *calloc(size_t count, size_t size)
{
    /*
    **  The calloc() function contiguously allocates enough space for count objects that
    **  are size bytes of memory each and returns a pointer to the allocated memory.
    **  The allocated memory is filled with bytes of value zero.
    */
    void     *ptr;

    pthread_mutex_lock(&g_mutex);
    ptr = NULL;
    ptr = calloc_twin(count, size);
    pthread_mutex_unlock(&g_mutex);
    return (ptr);
}

void    *reallocf(void *ptr, size_t size)
{
    /*
    ** The reallocf() function is identical to the realloc() function,
    ** except that it will free the passed pointer when the requested memory
    ** cannot be allocated.  This is a FreeBSD specific API designed to ease
    ** the problems with traditional coding styles for realloc
    ** causing memory leaks in libraries
    */
   void     *new_ptr;

   pthread_mutex_lock(&g_mutex);
   new_ptr = NULL;
   new_ptr = realloc(ptr, size);
   free(ptr);
   pthread_mutex_unlock(&g_mutex);
   return (new_ptr);
}

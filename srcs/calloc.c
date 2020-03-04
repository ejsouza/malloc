#include "../includes/malloc.h"

void        *calloc(size_t count, size_t size)
{
    /*
    **  The calloc() function contiguously allocates enough space for count objects that
    **  are size bytes of memory each and returns a pointer to the allocated memory.
    **  The allocated memory is filled with bytes of value zero.
    */
    size_t   request_size;
    void     *ptr;

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
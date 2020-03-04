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
   new_ptr = realloc(ptr, size);
   free(ptr);
   return (new_ptr);
}
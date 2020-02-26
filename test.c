#include "includes/malloc.h"
#include "./Libft/includes/libft.h"
#include <string.h>

int		main()
{
	ft_putstr("enter main()\n");
	char	*ptr;
	ptr = malloc(10);
	ft_putstr("1\n");
	strcpy(ptr, "hello\n");
	ft_putstr("\n2\n");
	ft_putstr(ptr);
	ft_putstr("\n2\n");
	free(ptr);
	ft_putstr("\n");
	return (0);
}

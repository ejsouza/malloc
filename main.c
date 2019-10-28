#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/resource.h>
#include <pthread.h>
#include <stdio.h> // to be deleteted
#include <string.h> // to be deleted

int				main(void)
{
	char *addr;
	int		pagesize;
	int		i;

	pagesize = getpagesize();
	i = 0;
	/*
	 * MMAP does return by pages, i.e here pagesize = 4096
	 * so no other number will be taken in account, if you put 4097 for example
	 * it will actually give you 2 pages or 4096 * 2 = 8192 and so on.
	 */
	addr = (char *) mmap(0, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC,
			MAP_ANON | MAP_PRIVATE, -1, 0 );
	
	while (i < pagesize - 1)
	{
		addr[i] = 'x';
		i++;
	}
	addr[pagesize - 2] = 'X';
	printf("%s\n", addr);
	printf("len = %lu\taddress %p\tpagesize - 1 = %i\n", strlen(addr), addr,
			pagesize - 1);
	return (0);
}

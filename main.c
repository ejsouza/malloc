#include "includes/malloc.h"
#include <stdlib.h>
#include <string.h>
#define TIMES_TO_RUN 5


int					main(int argc, char **argv)
{
	char		*addr[200];
	char		*addr1;
	char		*addr2;
	char		*addr3;
	char		*addr4;
	int		i;
	size_t		index;
	
	index = 26 * 4096; // 26 is the number of pages here
	if (argc != 2)
	{
		printf("usage %s <size>\n", argv[0]);
		return (1);
	}
	
	for (int i = 0; i < TIMES_TO_RUN; i++)
	{
		addr[i] = ft_malloc(16);
		addr[i][0] = 42;
	
		if (i == 110)
		{
			printf("AFTER CALLING A LOOP TO FREE 110 CHUNKS\n");
			show_alloc_mem();
			printf("\n---------------------------------------------------------------------\n");
			for (int j = 0; j < i; j++)
			{
				printf("%s %d\n", addr[j], j);
				ft_free(addr[j]);
			}

		}
		// if (i == 0) {
		// 	addr = ft_malloc(1024);
		// 	addr[0] = 42;
		// } else if (i == 1) {
		// 	addr1 = ft_malloc(1024);
		// 	addr1[0] = 42;
		// } else if (i == 2) {
		// 	addr2 = ft_malloc(1024);
		// 	addr2[0] = 42;
		// } else if (i == 3) {
		// 	addr3 = ft_malloc(1024);
		// 	addr3[0] = 42;
		// } else {
		// 	addr4 = ft_malloc(1024);
		// 	addr4[0] = 42;
		// }
	}
	printf("AFTER CALLING A LOOP TO FREE 110 CHUNKS\n");
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	for (int x = 0; x < TIMES_TO_RUN; x++)
	{
		if (x == 0 || x == 1 || x == 2)
			ft_free(addr[x]);
	}
	//printf("Before show_alloc_mem(2)\n");
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	//printf("After show_alloc_mem(2)\n");
	addr[0] = ft_malloc(16);
	//printf("After calling malloc() again\n");
	memcpy(addr[0], "Hello World!", 12);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	//printf(">>>{%s}[%p]<<<\n", addr[0], addr[0]);
	
	addr[1] = ft_malloc(16);
	memcpy(addr[1], "Hello World!", 12);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	addr4 = ft_malloc(16);
	memcpy(addr4, "Hello World!", 12);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	ft_free(addr4);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");

	for (int x = 0; x < TIMES_TO_RUN; x++)
	{
		if (x == 6 || x == 7 || x == 8)
			ft_free(addr[x]);
	}
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	addr4 = ft_malloc(32);
	memcpy(addr4, "Hello World!", 12);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	// printf("addr[%p][%c] 1\n", addr4, *addr4);
	// printf("-----------Before calling free(0)----------\n");
	// ft_free(addr3);
	// //printf("-----------Before calling free(1)----------\n");
	// ft_free(addr2);
	// printf("-----------Before calling free(2)----------\n");
	// ft_free(addr1);
	// printf("-----------Before calling free(3)----------\n");
	// ft_free(addr);
	// //ft_free(addr1);
	// addr4 = ft_malloc(1024);
	// addr4[0] = '?';
	// printf("addr[%p][%c] 2\n", addr4, *addr4);

	// t_block *end;
	// t_chunk *head;
	// end = g_zone[0];
	// head = (t_chunk *)addr4 - ONE;
	// head += sizeof(char);
	// printf("%p __________________ %p \t %p\n", end, head, head->next);
	// ft_free(addr4);
	addr[6] = ft_malloc(128);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	addr[7] = ft_malloc(48);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	addr[8] = ft_malloc(48);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	ft_free(addr[6]);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	addr[6] = ft_malloc(28);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	return (0);
}

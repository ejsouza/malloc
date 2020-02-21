#include "includes/malloc.h"
#include <stdlib.h>
#include <string.h>
#define TIMES_TO_RUN 5


int					main(int argc, char **argv)
{
	char		*addr[400];
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
		addr[i] = ft_malloc(1024);
		addr[i][0] = 42;
	
		if (i == 200)
		{
	// 		printf("AFTER CALLING A LOOP TO FREE 100 CHUNKS\n");
			show_alloc_mem();
			printf("\n---------------------------------------------------------------------\n");
	// 	// 	show_alloc_mem();
	// 	// 	printf("\n---------------------------------------------------------------------\n");
			for (int j = 100; j < 150; j++)
			{
	// 	// 	// 	printf("%s %d\n", addr[j], j);
				if (j % 2)
					ft_free(addr[j]);
			}
	// 	// 	ft_free(addr[i - 1]);
	// 	// 	ft_free(addr[i]);
/*		 	printf("show_alloc_mem() after calling first free()\n");
			show_alloc_mem();
			printf("\n---------------------------------------------------------------------\n");
*/	// 	// 	//ft_free(addr[1]);

		}
	}
	show_alloc_mem();
//	printf("\n---------------------------------------------------------------------\n");
	// ft_free(addr[3]);
	// ft_free(addr[2]);
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	// for (int x = 1; x < 4; x++)
	// {
	// 	if (x == 1 || x == 2 || x == 3)
	// 		ft_free(addr[x]);
	// }
	// printf("Before show_alloc_mem(2)\n");
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	// //printf("After show_alloc_mem(2)\n");
	//addr[0] = ft_malloc(24);
	//printf("After calling malloc() again\n");
	//memcpy(addr[0], "Hello World!", 12);
	//printf("In main before calling the first free(%p) after loop\n", addr[1]);
	//ft_free(addr[1]);
	//ft_free(addr[0]);
	//show_alloc_mem();
	//printf("\n---------------------------------------------------------------------\n");
	// ft_free(addr[150]);
	//printf("In main before calling free() with NULL\n");
	//ft_free(NULL);

/*
	addr[149] = ft_malloc(5000);
	memcpy(addr[149], "Hello World!", 12);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");

	addr[150] = ft_malloc(5000);
	memcpy(addr[150], "Hello World!", 12);
	show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	// ft_free(addr[150]);
	// show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	// //printf(">>>{%s}[%p]<<<\n", addr[0], addr[0]);

	addr[151] = ft_malloc(9000);
	memcpy(addr[151], "Hello World!", 12);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
	ft_free(addr[151]);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");

	addr[151] = ft_malloc(1024);
	memcpy(addr[151], "Hello World!", 12);
	show_alloc_mem();
	printf("\n---------------------------------------------------------------------\n");
*/	
	
	// addr[152] = ft_malloc(4096);
	// memcpy(addr[152], "Hello World!", 12);
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	// printf("========================================================================\n");
	// ft_free(addr[152]);
	// printf("========================================================================\n");
	// show_alloc_mem();
	// addr4 = ft_malloc(16);
	// memcpy(addr4, "Hello World!", 12);
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	// ft_free(addr4);
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");

	// for (int x = 0; x < TIMES_TO_RUN; x++)
	// {
	// 	if (x == 6 || x == 7 || x == 8)
	// 		ft_free(addr[x]);
	// }
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	// addr4 = ft_malloc(32);
	// memcpy(addr4, "Hello World!", 12);
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	// // printf("addr[%p][%c] 1\n", addr4, *addr4);
	// // printf("-----------Before calling free(0)----------\n");
	// // ft_free(addr3);
	// // //printf("-----------Before calling free(1)----------\n");
	// // ft_free(addr2);
	// // printf("-----------Before calling free(2)----------\n");
	// // ft_free(addr1);
	// // printf("-----------Before calling free(3)----------\n");
	// // ft_free(addr);
	// // //ft_free(addr1);
	// // addr4 = ft_malloc(1024);
	// // addr4[0] = '?';
	// // printf("addr[%p][%c] 2\n", addr4, *addr4);

	// // t_block *end;
	// // t_chunk *head;
	// // end = g_zone[0];
	// // head = (t_chunk *)addr4 - ONE;
	// // head += sizeof(char);
	// // printf("%p __________________ %p \t %p\n", end, head, head->next);
	// // ft_free(addr4);
	// addr[6] = ft_malloc(128);
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	// addr[7] = ft_malloc(48);
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	// addr[8] = ft_malloc(48);
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	// ft_free(addr[6]);
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	// addr[6] = ft_malloc(28);
	// show_alloc_mem();
	// printf("\n---------------------------------------------------------------------\n");
	return (0);
}

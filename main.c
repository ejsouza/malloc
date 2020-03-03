#include "includes/malloc.h"
#include <stdlib.h>
#include <string.h>
#define TIMES_TO_RUN 5
#define NINE	9
#define HEX		16


int					main(int argc, char **argv)
{
	char		*addr1;
	char		*addr2;
	char		*addr3;
	char		*addr4;
	int		i;
	size_t		index;
	
	index = 26 * 4096; // 26 is the number of pages here
	if (argc != 2)
	{
		ft_putstr("usage  <size>\n");
		return (1);
	}

	// Try to reproduce segfault =======================================

	//system("ls");

	addr1 = malloc(736);
	ft_memmove(addr1, "Hello World!", 13);
	addr2 = realloc(addr1 + 5, 800);
	addr3 = malloc(128);
	ft_memmove(addr3, "Hello world!", 12);
	ft_putstr("\n======================================================================\n");
	show_alloc_mem();
	ft_putstr("\n======================================================================\n");

//	size_t number_malloc = 12178;
	size_t number_malloc = 5000;
	char		*addr[number_malloc];
	i = 0;
	int y = 0;
	while (i < number_malloc)
	{
		addr[i] = malloc(i);
		if (addr[i] != NULL)
			ft_memmove(addr[i], "Helloc world", 12);
		i += HEX;
	}
	i = 0;
	while (i < number_malloc)
	{
		int tmp = i % 2;
		if (tmp)
			tmp = HEX + NINE;
		else
			tmp = HEX;
		if (i % 2)
			addr4 = realloc(addr[i], i + tmp);
		else if (!(i % 2) && ((i - tmp) > 0))
			addr4 = realloc(addr[i], i - tmp);
		else 
			addr4 = realloc(addr[i], i + tmp + tmp);
		i += HEX;
	}
	show_alloc_mem();
	// show_mem();
	// addr[102] = realloc(addr[1], 1000);
	// size_t addr_ptr = (size_t)addr1;
	// number_to_hex(addr_ptr, 16);
	// ft_putstr("\n");
	// ft_putstr("(");
	// ft_putstr(addr1);
	// ft_putstr(")");
	// ft_putstr("\n");
	// ft_putstr("first show_alloc_mem() BEFORE FIRST valid realloc()\n");
	// ft_putstr("\n======================================================================\n");
	// show_alloc_mem();
	// ft_putstr("\n======================================================================\n");
	// ft_putstr("\n\n");
	// ft_putstr("first show_alloc_mem() AFTER FIRST non valid realloc()\n");
	// ft_putstr("\n======================================================================\n");
	// show_alloc_mem();
	// ft_putstr("\n======================================================================\n");
	// addr2 = realloc(addr1, 800);

	// ft_putstr("first show_alloc_mem() AFTER SECOND non valid realloc()\n");
	// ft_putstr("\n======================================================================\n");
	// show_alloc_mem();
	// ft_putstr("\n======================================================================\n");

	// ft_putstr("\n-->\n");
	// ft_putstr(addr2);
	// ft_putstr("\n<--\n");

	// addr2 = realloc(addr1, 42);
	// ft_putstr("\n-->\n");
	// ft_putstr(addr2);
	// ft_putstr("\n<--\n");

	// ft_putstr("first show_alloc_mem() AFTER FIRST valid realloc()\n");
	// ft_putstr("\n======================================================================\n");
	// show_alloc_mem();
	// ft_putstr("\n======================================================================\n");

	// addr_ptr = (size_t)addr2;
	// number_to_hex(addr_ptr, 16);
	// ft_putstr("\n");
	// show_alloc_mem();
	// ft_putstr("\n======================================================================\n");

	// addr[101] = malloc(64);
	// ft_memmove(addr[101], "Hello World! 101", 17);
	// ft_putstr(addr[101]);
	// ft_putstr("\n======================================================================\n");
	// show_alloc_mem();
	// ft_putstr("\n======================================================================\n");

	// addr[102] = realloc(addr[101], 256);
	// ft_putstr(addr[102]);
	// ft_putstr("\n======================================================================\n");
	// show_alloc_mem();
	// ft_putstr("\n======================================================================\n");


	ft_putstr("\n----------------------END MAIN()-------------------------------\n");

// 	for (i = 0; i < TIMES_TO_RUN; i++)
// 	{
// 		addr[i] = ft_malloc(1024);
// 		addr[i][0] = 42;
	
// 		if (i == 200)
// 		{
// 	// 		printf("AFTER CALLING A LOOP TO FREE 100 CHUNKS\n");
// 			show_alloc_mem();
// 			printf("\n---------------------------------------------------------------------\n");
// 	// 	// 	show_alloc_mem();
// 	// 	// 	printf("\n---------------------------------------------------------------------\n");
// 			for (int j = 100; j < 150; j++)
// 			{
// 	// 	// 	// 	printf("%s %d\n", addr[j], j);
// 				if (j % 2)
// 					ft_free(addr[j]);
// 			}
// 	// 	// 	ft_free(addr[i - 1]);
// 	// 	// 	ft_free(addr[i]);
// /*		 	printf("show_alloc_mem() after calling first free()\n");
// 			show_alloc_mem();
// 			printf("\n---------------------------------------------------------------------\n");
// */	// 	// 	//ft_free(addr[1]);

// 		}
// 	}
// 	addr[i++] = ft_malloc(64);
// 	show_alloc_mem();
// 	int y = 0;
// 	for (; y < TIMES_TO_RUN; y++)
// 	{
// 		addr[i] = ft_malloc(4096);
// 		addr[i][0] = 42;
// 		i++;
// 	}
// 	show_alloc_mem();
// 	for (int x = 0; x < TIMES_TO_RUN; x++)
// 	{
// 		addr[i] = ft_malloc(5000);
// 		addr[i][0] = 42;
// 		i++;
// 	}
// 	show_alloc_mem();

/*
	i = 0;
	addr[i] = malloc(42);
	ft_memcpy(addr[i], "Hello world\n", ft_strlen("Hello world\n"));
	printf("%s\n", addr[i]);
	show_alloc_mem();
	addr[1] = ft_realloc(addr[i], 5);
	printf("=========================\n");
	show_alloc_mem();
	printf("=========================\n");
	printf("%s\n", addr[1]);
	ft_realloc(addr[1], 21);
	printf("%s\n", addr[1]);
	show_alloc_mem();
*/

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

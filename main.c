/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:36:39 by esouza            #+#    #+#             */
/*   Updated: 2019/10/30 15:32:25 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"
#include <stdlib.h>
#include <string.h>

t_block				block;

int					main(int argc, char **argv)
{
	char		*addr;
	int			i;
	t_chunk		chunk;
	
	if (argc != 2)
	{
		printf("usage %s <size>\n", argv[0]);
		return (1);
	}
//	printf("size of chunk = %zu\n", sizeof(t_chunk));
//	printf("before calling malloc\n");
	addr = (char *) malloc(atoi(argv[1]));
	block.data =  malloc(atoi(argv[1]) * getpagesize());
	strcpy(block.data, "Hello world!");
	printf("%s\n", block.data);
	printf("%p\t%c\n", block.data, (*(char *)block.data));

	for (i = 0; i < strlen("Hello world!"); i++)
	{
		printf("Addr %p\tValue %c\n", (char *)block.data + i, (*(char *)(block.data + i)));
	}
	printf("i = %d\n", getpagesize());
	while (i < 4095)
	{
		(*(char *)(block.data + i)) = 'x';
		i++;
	}
	memcpy((char *)block.data + 4076, (char *)"HELLO MOTHER FUCKER!", 20);
	printf("\n************************************************************\n");
	printf("%s\n", block.data);
	/*
	printf("after calling malloc\n");
	if (addr == NULL)
	{
		printf("Malloc failed\n");
		return (1);
	}
	addr[4095] = 42;
	printf("Addr = %c", addr[4095]);
	printf("start addres of memory %p\tbinary %p\n", addr, addr + 1);
	*/
	return (0);
}

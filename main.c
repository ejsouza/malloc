/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:36:39 by esouza            #+#    #+#             */
/*   Updated: 2019/11/08 14:39:54 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"
#include <stdlib.h>
#include <string.h>


int					main(int argc, char **argv)
{
	char		*addr;
	char		*addr1;
	char		*addr2;
	char		*addr3;
	int			i;
	
	if (argc != 2)
	{
		printf("usage %s <size>\n", argv[0]);
		return (1);
	}
	if (((addr = (char *) malloc(atoi(argv[1]))) == NULL))
	{
		printf("Malloc failed\n");
		return (1);
	}
//	addr[4095] = 42;
	addr1 = malloc(42);
	addr1[0] = 42;
	printf("<<<%p>>>\n", addr1);
	printf(">>>%p<<<\n", addr1 - 24);
	addr2 = malloc(42);
	addr2[0] = 42;
	printf("<<<%p>>>\n", addr2);
	printf(">>>%p<<<\n", addr2 - 24);
	addr3 = malloc(42);
	//addr = malloc(4096);
	//addr = malloc(4096);
	addr = malloc(4096);
	return (0);
}

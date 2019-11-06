/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:36:39 by esouza            #+#    #+#             */
/*   Updated: 2019/11/06 14:22:05 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"
#include <stdlib.h>
#include <string.h>


int					main(int argc, char **argv)
{
	char		*addr;
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

	addr[4095] = 42;
	addr = malloc(42);
	addr = malloc(42);
	addr = malloc(42);
	//addr = malloc(4096);
	//addr = malloc(4096);
	addr = malloc(4096);
	return (0);
}

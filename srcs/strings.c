/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 11:50:06 by esouza            #+#    #+#             */
/*   Updated: 2019/10/29 11:07:24 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t			ft_strlen_m(const char *s)
{
	size_t		len;

	len = 0;

	if (s == NULL)
		return (len);
	while (*s++)
		len++;
	return (len);
}

void		ft_putstr(char *str)
{
	write(1, str, ft_strlen_m(str));
}
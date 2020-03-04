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

size_t			ft_strlen(const char *s)
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
	write(1, str, ft_strlen(str));
}

void				ft_bzero(void *s, size_t n)
{
	int				i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (n)
	{
		str[i] = '\0';
		i++;
		n--;
	}
	s = str;
}

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*dst_cpy;
	unsigned char	*src_cpy;

	i = 0;
	dst_cpy = (unsigned char *)dst;
	src_cpy = (unsigned char *)src;
	while (n)
	{
		dst_cpy[i] = src_cpy[i];
		i++;
		n--;
	}
	dst = dst_cpy;
	return ((unsigned char *)dst);
}

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*dst_cpy;
	unsigned char			*src_cpy;

	src_cpy = (unsigned char *)src;
	dst_cpy = (unsigned char *)dst;
	if (src_cpy < dst_cpy)
		while (len--)
			dst_cpy[len] = src_cpy[len];
	else
		ft_memcpy(dst_cpy, src_cpy, len);
	return (dst_cpy);
}
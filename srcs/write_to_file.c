/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:11:57 by esouza            #+#    #+#             */
/*   Updated: 2020/03/09 10:11:59 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		ft_putstr_fd(char const *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void create_file_name(char *str)
{
    int     pid_id;
    char    file_name[32];
    int     len;
    int     reminder;

    pid_id = getpid();
    ft_bzero(file_name, 32);
    ft_bzero(str, 32);
    len = int_len(pid_id);
    if (pid_id < 0)
    {
        str = NULL;
        return ;
    }
    while (len)
    {
        reminder = pid_id % 10;
        str[len] = reminder + '0';
        len--;
        pid_id /= 10;
    }
    str[0] = '.';
    ft_memmove(str + ft_strlen(str), "_mem_historic", 13);
}

static void        number_2_hex(uint64_t numb, int base, char *address)
{
    uint64_t    remainder;
    int         i;
    char        number[42];
    char        hex[17];
    
    ft_memcpy(hex, "0123456789ABCDEF", 16);
    ft_bzero(number, 42);
    ft_bzero(address, 16);
    number[0] = '0';
    number[1] = 'x';
    i = 10;
    while (numb != 0 && i < 42)
    {
        remainder = numb % base;
        if (remainder < 10)
           number[i--] = 48 + remainder;
        else
           number[i--] = hex[remainder];
        numb /= base;
    }
    number[11] = 0;
    ft_memmove(address, number, 11);
    
}

static void write_size(char *str, size_t size)
{
    int     remainder;
    int     int_size;

    int_size = int_len(size);
    ft_bzero(str, 42);
    while (--int_size >= 0)
    {
        remainder = size % 10;
        str[int_size] = remainder + '0';
        size /= 10;
    }
}

void        write_to_file(void *ptr, size_t size)
{
    char    file_name[32];
    char    str[42];
    mode_t  mode;
    char    addr[16];
    int     fd;

    if (ptr == NULL || size < 0)
        return ;
    create_file_name(file_name);
    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, mode);
    if (fd < 0)
    {
        fprintf(stderr, "Can't open/create file %s!\n", file_name);
        return ;
    }
    number_2_hex((uint64_t)ptr, 16, addr);
    write_size(str, size);
    ft_putstr_fd(addr, fd);
    ft_putstr_fd("          ", fd);
    ft_putstr_fd(str, fd);
    ft_putstr_fd("\n", fd);
    close(fd);
}

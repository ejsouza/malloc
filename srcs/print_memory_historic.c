/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory_historic.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouza <esouza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:10:57 by esouza            #+#    #+#             */
/*   Updated: 2020/03/09 13:40:44 by esouza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		read_file(int fd)
{
	char		buff[80];
	char		ch;
	int			i;

	i = 0;
	while ((read(fd, &ch, 1)) > 0)
	{
		if (ch == '\n')
		{
			buff[++i] = '\0';
			ft_putstr(buff);
			ft_putstr("\n");
			i = 0;
		}
		else if (ch != '\n')
		{
			buff[i] = ch;
			i++;
		}
	}
}

void			delete_file(void)
{
	char		file_name[32];
	int			status;

	create_file_name(file_name);
	status = remove(file_name);
	if (status == 0)
	{
		ft_putstr("\033[0;32m");
		ft_putstr(file_name);
		ft_putstr(" file deleted successfully.\n");
		ft_putstr("\033[0m");
	}
	else
	{
		write(1, "\033[0;31m", 9);
		ft_putstr("Unable to delete the file\n\n");
		write(1, "\033[0m", 5);
	}
}

void			print_mem_hist_twin(void)
{
	char		file_name[32];
	int			fd;

	create_file_name(file_name);
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		ft_putstr("Can't open the file ");
		ft_putstr(file_name);
		ft_putstr("\n");
		return ;
	}
	ft_putstr("\nMEMORY HISTORY       SIZE\n");
	read_file(fd);
	close(fd);
}

void			print_memory_historic(void)
{
	pthread_mutex_lock(&g_mutex);
	print_mem_hist_twin();
	pthread_mutex_unlock(&g_mutex);
}

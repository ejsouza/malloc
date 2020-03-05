#include "../includes/malloc.h"

static void read_file(int fd)
{
    char    buff[80];
    char    ch;
    int     i;

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

void    print_memory_historic(void)
{
    char    file_name[32];
    // char    buff[80];
    // char    buf;
    int     fd;
    // int     ret;

    create_file_name(file_name);
    if ((fd = open(file_name, O_RDONLY)) == -1)
    {
        fprintf(stderr, "Can't open the file %s!\n", file_name);
        return ;
    }
    ft_putstr("\nMEMORY HISTORY       SIZE\n");
    read_file(fd);
    // ret = 0;
    // while ((read(fd, &buf, 1)) > 0)
    // {
    //     if (buf != '\n')
    //     {
    //         buff[ret] = buf;
    //         ret++;
    //     }
    //     else if (buf == '\n')
    //     {
    //         buff[++ret] = '\0';
    //         ft_putstr(buff);
    //         ft_putstr("\n");
    //         ret = 0;
    //     }
    // }
    close(fd);
}
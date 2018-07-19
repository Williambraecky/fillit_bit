/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:10:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/19 14:38:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_exit_putendl(char *str, int fd)
{
	ft_putendl_fd(str, fd);
	exit(0);
}

void	ft_empty_map(char *str, size_t width)
{
	size_t	i;

	i = 0;
	while (i < (width + 1) * (width))
	{
		if (i % (width + 1) == width)
			str[i] = '\n';
		else
			str[i] = '.';
		i++;
	}
	str[i] = '\0';
}

void	ft_print_map(t_tetriminos *list, size_t i, size_t map_size)
{
	char	str[map_size * (map_size + 1) + 1];
	size_t	x;
	size_t	y;

	ft_empty_map(str, map_size);
	while (i)
	{
		y = 0;
		while (y < list->height)
		{
			x = 0;
			while (x < list->width)
			{
				if ((list->active_bits >> (16 * (y) + x)) & 1)
					str[(list->y + y) * (map_size + 1) + x + list->x] = list->c;
				x++;
			}
			y++;
		}
		i--;
		list++;
	}
	ft_putstr_fd(str, 1);
}

int		main(int argc, char **argv)
{
	t_tetriminos	tetris[26];
	uint16_t		map[19];
	size_t			i;
	int				size;
	int				fd;

	ft_bzero(map, sizeof(uint16_t) * 19);
	if (argc == 1 || argc > 2)
		ft_exit_putendl("usage: ./fillit fillit_file", 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit_putendl("error", 1);
	i = ft_parse_tetris(tetris, fd);
	if (i == 0)
		ft_exit_putendl("error", 1);
	if (close(fd) == -1)
		ft_exit_putendl("error", 1);
	size = ft_tetris_resolve(tetris, i, map);
	ft_print_map(tetris, i, size);
	return (0);
}

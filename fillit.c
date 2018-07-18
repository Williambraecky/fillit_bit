/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:10:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/13 11:24:49 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_exit_putendl(char *str, int fd)
{
	ft_putendl_fd(str, fd);
	exit(0);
}

char	*ft_empty_map(size_t width)
{
	char	*new;
	size_t	i;

	new = ft_strnew((width + 1) * (width));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < (width + 1) * (width))
	{
		if (i % (width + 1) == width)
			new[i] = '\n';
		else
			new[i] = '.';
		i++;
	}
	return (new);
}

void	ft_print_map(t_tetriminos *list, size_t i, size_t map_size)
{
	char	*str;
	size_t	x;
	size_t	y;

	str = ft_empty_map(map_size);
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
	uint16_t		map[16];
	size_t			i;
	int				size;
	int				fd;

	ft_bzero(map, sizeof(uint16_t) * 16);
	if (argc == 1 || argc > 2)
		ft_exit_putendl("usage: ./fillit fillit_file", 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit_putendl("error", 1);
	i = ft_parse_tetris(tetris, fd);
	if (i == 0)
		ft_exit_putendl("error", 1);
	size = ft_tetris_resolve(tetris, i, map);
	ft_print_map(tetris, i, size);
	return (0);
}

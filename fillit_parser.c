/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:19:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/19 12:42:30 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetriminos	ft_new_tetris(size_t index)
{
	t_tetriminos	new;

	new.active_bits = 0;
	new.similar = NULL;
	new.c = 'A' + index;
	new.x = 0;
	new.y = 0;
	new.width = 0;
	new.height = 0;
	return (new);
}

int				ft_parse_tetris(t_tetriminos *tetris, int fd)
{
	char	buffer[21];
	int		i;
	int		j;

	buffer[20] = '\0';
	i = 0;
	while ((j = read(fd, buffer, 20)) != 0)
	{
		if (j != 20 || j == -1 || i == 26)
			return (0);
		tetris[i] = ft_new_tetris(i);
		if (!ft_tetris_isvalid(tetris + i, buffer))
			return (0);
		j = i++;
		while (j-- && tetris[i - 1].similar != NULL)
			if (tetris[j].active_bits == tetris[i - 1].active_bits)
				(tetris + i - 1)->similar = (tetris + j);
		if (read(fd, buffer, 1) == 0)
			return (i);
		if (buffer[0] != '\n')
			return (0);
	}
	if (j == 0)
		return (0);
	return (i);
}

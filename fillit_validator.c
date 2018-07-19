/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:30:23 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/19 14:29:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

char	ft_tetris_charat(char *data, int x, int y)
{
	if (x < 0 || y < 0 || x > 4 || y > 4)
		return ('.');
	return (data[x + (y * 5)]);
}

int		ft_tetris_countneighbours(char *data, int x, int y)
{
	return ((ft_tetris_charat(data, x - 1, y) == '#') +
			(ft_tetris_charat(data, x, y - 1) == '#') +
			(ft_tetris_charat(data, x + 1, y) == '#') +
			(ft_tetris_charat(data, x, y + 1) == '#'));
}

void	ft_tetris_process(t_tetriminos *tetris, char *data, size_t t_data[])
{
	size_t	i;
	size_t	j;

	if (t_data[4] != 4)
		return ;
	j = 0;
	while (j < tetris->height)
	{
		i = 0;
		while (i < tetris->width)
		{
			if (ft_tetris_charat(data,
				t_data[0] + i, t_data[2] + j) == '#')
				tetris->active_bits |= (1L << (16 * j + i));
			i++;
		}
		j++;
	}
}

int		ft_tetris_validateform(t_tetriminos *tetris, char *data,
		size_t t_data[])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (ft_tetris_charat(data, j, i) != '#')
				continue ;
			t_data[0] = (size_t)j < t_data[0] ? (size_t)j : t_data[0];
			t_data[1] = (size_t)j > t_data[1] ? (size_t)j : t_data[1];
			t_data[2] = (size_t)i < t_data[2] ? (size_t)i : t_data[2];
			t_data[3] = (size_t)i > t_data[3] ? (size_t)i : t_data[3];
			t_data[5] += ft_tetris_countneighbours(data, j, i);
			if (++t_data[4] > 4)
				return (0);
		}
	}
	tetris->width = t_data[1] - t_data[0] + 1;
	tetris->height = t_data[3] - t_data[2] + 1;
	ft_tetris_process(tetris, data, t_data);
	return (t_data[4] == 4 && t_data[5] >= 6);
}

int		ft_tetris_isvalid(t_tetriminos *tetris, char *data)
{
	size_t	t_data[6];
	size_t	i;

	i = 0;
	while (i < 20)
	{
		if (data[i] == '\0' && i != 19)
			return (0);
		if (i % 5 == 4 && data[i] != '\n')
			return (0);
		if (i % 5 != 4 && data[i] != '.' && data[i] != '#')
			return (0);
		i++;
	}
	t_data[0] = 3;
	t_data[1] = 0;
	t_data[2] = 3;
	t_data[3] = 0;
	t_data[4] = 0;
	t_data[5] = 0;
	if (!ft_tetris_validateform(tetris, data, t_data))
		return (0);
	return (1);
}

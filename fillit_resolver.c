/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 16:00:33 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/19 14:38:48 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

void	ft_toggle_placement(t_tetriminos *tetris, uint16_t *map,
		size_t x, size_t y)
{
	*(uint64_t *)(map + y) ^= (tetris->active_bits << x);
}

int		ft_try_placement(t_tetriminos *tetris, uint16_t *map,
		size_t x, size_t y)
{
	return ((*(uint64_t *)(map + y) & (tetris->active_bits << x)) == 0);
}

size_t	ft_calculate_x(t_tetriminos *tetris)
{
	if (tetris->similar == NULL)
		return (0);
	if (tetris->similar->y == tetris->y)
		return (tetris->similar->x + tetris->width);
	return (0);
}

int		ft_find_solution(t_tetriminos *list, size_t sol_size,
		size_t max, uint16_t *map)
{
	list->y = list->similar != NULL ? list->similar->y : 0;
	while (list->y + list->height - 1 < sol_size)
	{
		list->x = ft_calculate_x(list);
		while (list->x + list->width - 1 < sol_size)
		{
			if (ft_try_placement(list, map, list->x, list->y))
			{
				ft_toggle_placement(list, map, list->x, list->y);
				if (list->c - 'A' == (char)max - 1 ||
						ft_find_solution(list + 1, sol_size, max, map))
					return (1);
				ft_toggle_placement(list, map, list->x, list->y);
			}
			list->x++;
		}
		list->y++;
	}
	list->x = 0;
	list->y = 0;
	return (0);
}

int		ft_tetris_resolve(t_tetriminos *list, size_t len, uint16_t *map)
{
	size_t	sol_size;

	sol_size = 2;
	while (sol_size * sol_size < len * 4)
		sol_size++;
	while (!ft_find_solution(list, sol_size, len, map) && sol_size < 16)
	{
		ft_bzero(map, sizeof(uint16_t) * 19);
		sol_size++;
	}
	return ((int)sol_size);
}

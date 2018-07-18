/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 13:08:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/05 15:14:52 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include "libft.h"

typedef struct		s_tetriminos
{
	uint64_t			active_bits;
	struct s_tetriminos	*similar;
	char				c;
	size_t				x;
	size_t				y;
	size_t				width;
	size_t				height;
}					t_tetriminos;

int					ft_tetris_isvalid(t_tetriminos *tetris, char *data);
int					ft_parse_tetris(t_tetriminos *tetris, int fd);
int					ft_tetris_resolve(t_tetriminos *tetris, size_t len,
										uint16_t *map);
char				ft_solution_charat(char *solution, size_t x, size_t y);

#endif

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/14 12:58:31 by wbraeckm          #+#    #+#              #
#    Updated: 2018/07/19 12:48:42 by wbraeckm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CC = gcc

FLAGS = -Wall -Wextra -Werror

ITEMS = fillit.c fillit_parser.c \
		ft_strlen.c ft_memset.c ft_bzero.c \
		ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c \
		fillit_validator.c fillit_resolver.c

SRCS = $(ITEMS)

OBJ = $(ITEMS:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

noflags:
	$(CC) -c $(SRCS)
	$(CC) -o $(NAME) $(OBJ)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

norm:
	norminette $(SRCS)

.PHONY: all clean fclean re norm

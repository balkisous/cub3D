# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 00:03:43 by ddecourt          #+#    #+#              #
#    Updated: 2021/12/27 02:42:16 by ddecourt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/cub3d.c \
			srcs/parsing/check_map.c \
			srcs/parsing/check_texture.c \
			srcs/parsing/store_map.c \

OBJS	= ${SRCS:.c=.o}

NAME	= Cub3D

HEADER	= mlx/mlx.h 

CC		= clang

CFLAGS	= -Wall -Wextra -Werror -g3

RM = rm -f

.c .o:
	$(CC) $(CFLAGS) -Imlx -Lmlx -lmlx -O3 -c $< -o $@ 

$(NAME): $(OBJS)
		make -C libft
		make -C mlx
		$(CC) $(CFLAGS) $(OBJS)  -Imlx -Lmlx -lmlx -I -L./libft/ -Imlx -lXext -lX11 -lm ./libft/libft.a -o ${NAME}

all:	${NAME}

clean:
		make clean -C libft
		make clean -C mlx
		${RM} ${OBJS}

fclean: clean	
		make fclean -C libft
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
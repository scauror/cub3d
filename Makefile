# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scarpent <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 07:24:48 by scarpent          #+#    #+#              #
#    Updated: 2024/01/29 08:23:56 by scarpent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
FLAG = -Wall -Wextra -Werror -g3
LIBMLX = MLX42/build/libmlx42.a

SRC = main.c get_next_line.c gnl_utils.c error.c ft_split.c \
		map.c map_chk.c map_chk_elem.c map_chk_content.c \
		render.c render_walls.c rays_intersec.c ray_casting.c \
		player_moves.c utils.c utils2.c utils3.c

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all : $(OBJ_DIR) $(NAME)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o : %.c
	$(CC) $(FLAG) -c $< -o $@

$(LIBMLX):
	(cd MLX42 && cmake -B build && cmake --build build -j4)

$(NAME) : $(LIBMLX) $(OBJ)
	$(CC) $(OBJ) $(LIBMLX) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

clean :
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 18:57:48 by hasaliho          #+#    #+#              #
#    Updated: 2025/10/25 21:45:51 by hasaliho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = sandbox
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lmlx -lXext -lX11 -lm

SRC = main.c player.c test_map.c mlx_setup.c hooks.c cleanup.c render.c utils.c minimap.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all clean
	./$(NAME)

.PHONY: all clean fclean re run

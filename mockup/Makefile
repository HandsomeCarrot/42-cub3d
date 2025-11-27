# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 18:57:48 by hasaliho          #+#    #+#              #
#    Updated: 2025/10/17 07:26:08 by hasaliho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = sandbox
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -lXext -lX11 -lm

SRC = main.c render.c render_utils.c raycast_debug.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

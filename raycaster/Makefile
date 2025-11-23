# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 18:57:48 by hasaliho          #+#    #+#              #
#    Updated: 2025/11/21 18:32:32 by hasaliho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = sandbox
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Detect operating system
UNAME_S := $(shell uname -s)

# Set platform-specific flags
ifeq ($(UNAME_S),Darwin)
    # macOS with Metal MLX
    MLX_FLAGS = -lmlx -framework Metal -framework MetalKit
else ifeq ($(UNAME_S),Linux)
    # Linux with X11 MLX
    MLX_FLAGS = -lmlx -lXext -lX11 -lm
endif

SRC = main.c player.c test_map.c mlx_setup.c hooks.c cleanup.c render.c utils.c minimap/minimap.c movement.c minimap/minimap_utils.c
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


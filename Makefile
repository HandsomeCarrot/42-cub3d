# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/30 18:01:26 by vpoka             #+#    #+#              #
#    Updated: 2025/08/30 18:15:39 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = objs
LIBFT_DIR = libft
INC_DIR = include

LIBFT = $(LIBFT_DIR)/libft.a
INCLUDE = -I$(INC_DIR) -I$(LIBFT_DIR)

SRCS = $(SRC_DIR)/*

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean:
	rm -rf $(OBJ_DIR) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

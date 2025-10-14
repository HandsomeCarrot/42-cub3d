# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/30 18:01:26 by vpoka             #+#    #+#              #
#    Updated: 2025/10/14 10:53:00 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----VARIABLES-----#

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -MD -MP

INCLUDE = -Iinclude -Ilibft
COMP = $(CC) $(CFLAGS) $(INCLUDE)

S = src
SRCS =	$(addprefix $(S)/, \
		main.c)

B = build
OBJS = $(SRCS:$(S)/%.c=$(B)/%.o)
DEPS = $(OBJS:.o=.d)
LIBFT = libft/libft.a

#-----COLORS-----#

RST = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m

#-----RULES-----#

-include $(DEPS)

all: $(NAME)

$(B):
	@ mkdir -p $(B)
	@ printf "$(YELLOW)$(NAME): compiling...$(RST)\n"

$(B)/%.o: $(S)/%.c
	$(COMP) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(B) $(OBJS)
	$(COMP) $(OBJS) $(LIBFT) -o $(NAME)
	@ printf "$(GREEN)$(NAME) built successfully!$(RST)\n"

clean:
	@ rm -rf $(B)
	@ printf "$(RED)deleted BUILD files$(RST)\n"
	@ make -C libft clean

fclean: clean
	@ rm -f $(NAME)
	@ printf "$(RED)deleted PROGRAM file$(RST)\n"
	make -C libft fclean

re: fclean all

run: re
	@ printf "$(CYAN)$(NAME): starting...$(RST)\n"
	@ ./$(NAME)

.PHONY: all clean fclean re run

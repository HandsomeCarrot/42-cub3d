# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/30 18:01:26 by vpoka             #+#    #+#              #
#    Updated: 2025/10/14 21:00:17 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----VARIABLES-----#

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDE = -Iinclude -Ilibft/include
COMP = $(CC) $(CFLAGS) $(INCLUDE)

LIBFT = libft/libft.a

S = src
SRCS =	$(addprefix $(S)/, \
		main.c)

B = build
OBJS = $(SRCS:$(S)/%.c=$(B)/%.o)
DEPS = $(OBJS:.o=.d)

#-----COLORS-----#

RST = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m

#-----LOG LEVELS-----#

INFO = $(BLUE)
WARNING = $(YELLOW)
ERROR = $(RED)
SUCCESS = $(GREEN)
DEBUG = $(MAGENTA)

#-----LOG FUNCTION-----#

# Usage: $(call log,LEVEL,message)
# Example: $(call log,INFO,Building library...)
define log
	@ printf "$($(1))[$(1)]$(RST) $(2)\n"
endef

#-----RULES-----#

all: $(NAME)

$(B):
	@ mkdir -p $(B)
	$(call log,INFO,Created $(B) directory for $(NAME))

COMPILED_FILES = 0
$(B)/%.o: $(S)/%.c
	$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
	$(call log,DEBUG,Compiling [$(COMPILED_FILES)/$(TOTAL_FILES)]: $<)
	@ $(COMP) -MD -MP -c $< -o $@

$(NAME): TOTAL_FILES = $(words $(SRCS))
$(NAME): $(B) $(OBJS)
	@ make complete --directory=libft
	$(call log,INFO,building $(NAME))
	@ $(COMP) $(OBJS) $(LIBFT) -o $(NAME)
	$(call log,SUCCESS,$(NAME) built successfully!)

clean:
	@ rm -rf $(B)
	$(call log,WARNING,deleted $(B) directory for $(NAME)!)
	@ make clean --directory=libft

fclean: clean
	@ rm -f $(NAME)
	$(call log,WARNING,deleted $(NAME)!)
	@ make fclean --directory=libft

re: fclean all

run: re
	$(call log,INFO,executing $(NAME))
	@ ./$(NAME)

.PHONY: all clean fclean re run

-include $(DEPS)
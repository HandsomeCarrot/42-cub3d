# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/30 18:01:26 by vpoka             #+#    #+#              #
#    Updated: 2025/10/16 18:01:23 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----VARIABLES-----#

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror
DPFLAGS = -MP -MD
MLXFLAGS = -lmlx -lXext -lX11

INCLUDE = -Iinclude -Ilibft/include
COMP = $(CC) $(CFLAGS) $(INCLUDE)

LIBFT = libft/libft.a

S = src
SRCS =	$(addprefix $(S)/, \
		main.c \
		$(addprefix logging/, \
		logging.c) \
		$(addprefix inits/, \
		main_init.c) \
		$(addprefix cleanup/, \
		main_cleanup.c))

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

#-----RUN IN DIRECTORY FUNCTION-----#

# Usage: $(call run_in_dir,directory_path,make_command)
# Example: $(call run_in_dir,libft,complete)
define run_in_dir
	@ printf "\n"
	@ make $(2) -C $(1)
	@ printf "\n"
endef

#-----RULES-----#

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(call log,INFO,building $(NAME))
	@ $(COMP) $(MLXFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	$(call log,SUCCESS,$(NAME) built successfully!)

$(LIBFT):
	$(call run_in_dir,libft)

$(B):
	@ mkdir -p $(B)
	$(call log,DEBUG,Created $(B) directory for $(NAME))

$(B)/%.o: $(S)/%.c | $(B)
	$(call log,DEBUG,Compiling $<)
	@ mkdir -p $(@D)
	$(call log,DEBUG,Created directory $(@D))
	@ $(COMP) $(DPFLAGS) -c $< -o $@

clean:
	@ rm -rf $(B)
	$(call log,WARNING,deleted $(B) directory for $(NAME)!)
	$(call run_in_dir,libft,clean)

fclean: clean
	@ rm -f $(NAME)
	$(call log,WARNING,deleted $(NAME)!)
	$(call run_in_dir,libft,fclean)

re: fclean all

run: re
	@ printf "\n"
	$(call log,INFO,executing $(NAME))
	@ ./$(NAME)

#-----LOG LEVEL RULES-----#

log0: CFLAGS += -DLOGGING_LEVEL=0
log0: re
	$(call log,INFO,logging level set to 0)

log2: CFLAGS += -DLOGGING_LEVEL=2
log2: re
	$(call log,INFO,logging level set to 2)

log3: CFLAGS += -DLOGGING_LEVEL=3
log3: re
	$(call log,INFO,logging level set to 3)

log4: CFLAGS += -DLOGGING_LEVEL=4
log4: re
	$(call log,INFO,logging level set to 4)

.PHONY: all libft clean fclean re run log0 log2 log3 log4

-include $(DEPS)

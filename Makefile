# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/30 18:01:26 by vpoka             #+#    #+#              #
#    Updated: 2025/11/25 18:21:56 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----VARIABLES-----#

NAME := cub3d
LIBFT := libft/libft.a

CC := cc

CFLAGS := -Wall -Wextra -Werror
DPFLAGS := -MP -MD
LIBS := -lmlx -lXext -lX11

INCLUDE := -Iinclude -Ilibft
COMP := $(CC) $(CFLAGS) $(INCLUDE)

RM := rm -f

S := src

CLEANUP_SRCS :=	$(addprefix cleanup/, \
				cleanup_main.c \
				cleanup_strings.c)

LOGGING_SRCS :=	$(addprefix logging/, \
				logger.c \
				memory_logger.c)

PARSING_SRCS :=	$(addprefix parsing/, \
				parse.c \
				$(addprefix config/, \
				parse_colors.c \
				identify_textures.c \
				parse_textures.c) \
				$(addprefix logging/, \
				log_parsing_info.c \
				log_parsing_error.c) \
				$(addprefix map/, \
				save_map_data.c \
				read_map_file.c \
				extract_map_layout.c \
				process_map_lines.c \
				check_neighbors.c \
				validate_map.c) \
				$(addprefix player/, \
				locate_player.c) \
				$(addprefix utils/, \
				manage_arrays.c \
				check_chars.c \
				manage_colors.c \
				manage_files.c \
				check_lines.c \
				read_file_content.c) \
				$(addprefix validation/, \
				validate_content.c))

SRCS :=	$(addprefix $(S)/, \
		main.c \
		$(CLEANUP_SRCS) \
		$(LOGGING_SRCS) \
		$(PARSING_SRCS))

B := build
OBJS := $(SRCS:$(S)/%.c=$(B)/%.o)
DEPS := $(OBJS:%.o=%.d)

#-----COLORS-----#

RST := \033[0m
RED := \033[1;31m
GREEN := \033[1;32m
YELLOW := \033[1;33m
BLUE := \033[1;34m
MAGENTA := \033[1;35m
CYAN := \033[1;36m

#-----LOG LEVELS-----#

INFO := $(BLUE)
WARNING := $(YELLOW)
ERROR := $(RED)
SUCCESS := $(GREEN)
DEBUG := $(MAGENTA)

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
	$(call log,DEBUG,changing directory to $(1))
	@ make $(2) -C $(1)
	$(call log,DEBUG,returning from directory $(1))
endef

#-----RULES-----#

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(call log,INFO,building $(NAME))
	@ $(COMP) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	$(call log,SUCCESS,$(NAME) built successfully!)

$(LIBFT):
	$(call run_in_dir,libft)

$(B)/%.o: $(S)/%.c
	$(call log,INFO,Compiling $<)
	@ mkdir -p $(@D)
	@ $(COMP) $(DPFLAGS) -c $< -o $@

clean:
	@ $(RM) -r $(B)
	$(call log,WARNING,deleted $(B) directory for $(NAME)!)
	$(call run_in_dir,libft,clean)

fclean: clean
	@ $(RM) $(NAME)
	$(call log,WARNING,deleted $(NAME)!)
	$(call run_in_dir,libft,fclean)

re: fclean all

run: all
	@ printf "\n"
	$(call log,INFO,executing $(NAME))
	@ ./$(NAME) ./assets/maps/basic.cub

#-----LOG LEVEL RULES-----#

error: COMP += -DLOGGING_LEVEL=0
error: re
	$(call log,INFO,logging level set to ERROR)

warning: COMP += -DLOGGING_LEVEL=1
warning: re
	$(call log,INFO,logging level set to WARNING)

info: COMP += -DLOGGING_LEVEL=2
info: re
	$(call log,INFO,logging level set to INFO)
                 
debug: COMP += -DLOGGING_LEVEL=3
debug: re
	$(call log,INFO,logging level set to DEBUG)

.PHONY: all libft clean fclean re run error warning info debug

-include $(DEPS)

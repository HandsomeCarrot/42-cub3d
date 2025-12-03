# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/30 18:01:26 by vpoka             #+#    #+#              #
#    Updated: 2025/12/03 23:13:43 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----VARIABLES-----#

NAME := cub3d
LIBFT := libft/libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror
DPFLAGS := -MP -MD

INCLUDE := -Iinclude -Ilibft
LIBS := -Llibft -lft -lmlx -lXext -lX11 -lm
COMP := $(CC) $(CFLAGS) $(INCLUDE)

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

RAYCASTER_SRCS :=	$(addprefix raycaster/, \
					cleanup.c \
					hooks.c \
					movement.c \
					utils.c \
					$(addprefix minimap/, \
					minimap.c \
					minimap_utils.c) \
					$(addprefix render/, \
					render.c \
					perform_dda.c \
					drawing_utils.c) \
					$(addprefix setup/, \
					texture_utils.c \
					player_setup.c \
					mlx_setup.c))

S := src
SRCS :=	$(addprefix $(S)/, \
		main.c \
		$(CLEANUP_SRCS) \
		$(LOGGING_SRCS) \
		$(PARSING_SRCS) \
		$(RAYCASTER_SRCS))

B := build
OBJS := $(SRCS:$(S)/%.c=$(B)/%.o)
DEPS := $(OBJS:%.o=%.d)

#-----COLORS-----#

GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RESET = \033[0m

#-----PRINTING TOOLS-----#

# Usage: $(call print_target, target_name)
define print_target
	@printf "$(BLUE)🛠️  Compiling target: $(CYAN)$(1)$(RESET)\n"
endef

# Usage: $(call print_compile, file_name)
define print_compile
	@printf "$(YELLOW)🔧 Compiling: $(RESET)$(1)\n"
endef

# Usage: $(call print_clean, message)
define print_clean
	@printf "$(RED)🧹 $(1)$(RESET)\n"
endef

# Usage: $(call print_success, message)
define print_success
	@printf "$(GREEN)✨ $(1)$(RESET)\n"
endef

#-----RUN IN DIRECTORY FUNCTION-----#

# Usage: $(call run_in_dir,directory_path,make_command)
# Example: $(call run_in_dir,libft,complete)
define run_in_dir
	@printf "$(BLUE)📂 Entering directory: $(CYAN)$(1)$(RESET)\n"
	@make $(2) -C $(1) --no-print-directory
	@printf "$(BLUE)📂 Leaving directory: $(CYAN)$(1)$(RESET)\n"
endef

#-----RULES-----#

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(call print_target, $(NAME))
	@$(COMP) $(OBJS) $(LIBS) -o $(NAME)
	$(call print_success, $(NAME) ready!)

$(LIBFT): FORCE
	$(call run_in_dir,libft,)

FORCE:

$(B)/%.o: $(S)/%.c
	@mkdir -p $(@D)
	$(call print_compile, $<)
	@$(COMP) $(DPFLAGS) -c $< -o $@

clean:
	@rm -rf $(B)
	$(call print_clean, Removed build directory)
	$(call run_in_dir,libft,clean)

fclean: clean
	@rm -f $(NAME)
	$(call print_clean, Removed executable)
	$(call run_in_dir,libft,fclean)

re: fclean all

run: re
	@printf "$(BLUE)🚀 Running $(NAME)...$(RESET)\n"
	@printf "$(CYAN)--------------------------------$(RESET)\n"
	@./$(NAME) ./assets/maps/valid/basic.cub

#-----LOG LEVEL RULES-----#

error: COMP += -DLOGGING_LEVEL=0 re

warning: COMP += -DLOGGING_LEVEL=1 re

info: COMP += -DLOGGING_LEVEL=2 re
                 
debug: COMP += -DLOGGING_LEVEL=3 re

.PHONY: all clean fclean re run FORCE error warning info debug

-include $(DEPS)

#-----VARIABLES-----#

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -MD -MP

INCLUDE = -Iinclude
COMP = $(CC) $(CFLAGS) $(INCLUDE)

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

#-----RULES-----#

-include $(DEPS)

all: $(NAME)

$(B):
	@ mkdir -p $(B)
	@ printf "$(YELLOW)$(NAME): compiling...$(RST)\n"

$(B)/%.o: $(S)/%.c
	$(COMP) -c $< -o $@

$(NAME): $(B) $(OBJS)
	$(COMP) $(OBJS) -o $(NAME)
	@ printf "$(GREEN)$(NAME) built successfully!$(RST)\n"

clean:
	@ rm -rf $(B)
	@ printf "$(RED)deleted BUILD files$(RST)\n"

fclean: clean
	@ rm -f $(NAME)
	@ printf "$(RED)deleted PROGRAM file$(RST)\n"

re: fclean all

run: re
	@ printf "$(CYAN)$(NAME): starting...$(RST)\n"
	@ ./$(NAME)

.PHONY: all clean fclean re run

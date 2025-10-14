# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 12:43:39 by vpoka             #+#    #+#              #
#    Updated: 2025/10/14 16:29:18 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----VARIABLES-----#

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -MD -MP

INC = -Iinclude
COMP = $(CC) $(CFLAGS) $(INC)

ARNAME = ar rcs $(NAME)

S = src
SRCS =	$(addprefix $(S)/, \
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c)

BONUS_SRCS =	$(addprefix $(S)/, \
				ft_lstnew_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstmap_bonus.c \
				ft_lstsize_bonus.c)

B = build
OBJS = $(SRCS:$(S)/%.c=$(B)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(S)/%.c=$(B)/%.o)
ALL_OBJS = $(OBJS) $(BONUS_OBJS)

DEPS = $(OBJS:.o=.d) $(BONUS_OBJS:.o=.d)

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
	@ printf "$(YELLOW)$(NAME): compiling ...$(RST)\n"

$(B)/%.o: $(S)/%.c
	$(COMP) -c $< -o $@

$(NAME): $(B) $(OBJS)
	$(ARNAME) $(OBJS)
	@ printf "$(GREEN)$(NAME) (basic) built successfully!$(RST)\n"

bonus: $(B) $(BONUS_OBJS)
	$(ARNAME) $(BONUS_OBJS)
	@ printf "$(GREEN)$(NAME) (bonus) built successfully!$(RST)\n"

complete: $(B) $(ALL_OBJS)
	$(ARNAME) $(ALL_OBJS)
	@ printf "$(GREEN)$(NAME) (complete) built successfully!$(RST)\n"

clean:
	@ rm -rf $(B)
	@ printf "$(RED)deleted BUILD files$(RST)\n"

fclean: clean
	@ rm -f $(NAME)
	@ printf "$(RED)deleted LIBRARY file$(RST)\n"

re: fclean $(NAME)

.PHONY: all, bonus, complete, clean, fclean, re

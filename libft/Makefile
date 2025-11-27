# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/19 10:07:29 by vpoka             #+#    #+#              #
#    Updated: 2025/10/28 00:11:43 by vpoka            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----VARIABLES-----#

NAME := libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror
DPFLAGS := -MP -MD
INCLUDE := -I.

ARNAME := ar rcs $(NAME)
RM := rm -f

LIBFT := libft
LIBFT_SRCS :=	$(addprefix $(LIBFT)/, \
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
		ft_toupper.c \
		ft_lstnew_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c)

GNL := getNextLine
GNL_SRCS :=	$(addprefix $(GNL)/, \
				get_next_line_bonus.c \
				get_next_line_utils_bonus.c)

SRCS := $(LIBFT_SRCS) $(GNL_SRCS)
B := build
OBJS := $(SRCS:%.c=$(B)/%.o)
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

#-----RULES-----#

all: $(NAME)

$(NAME): $(OBJS)
	$(call log,INFO,Linking $(NAME) (standard functions))
	@ $(ARNAME) $^
	@ $(call log,SUCCESS,$(NAME) linked successfully!)\

$(B)/%.o: %.c
	$(call log,INFO,Compiling $<)
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) $(DPFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@ $(RM) -r $(B)
	$(call log,WARNING,deleted $(B) directory for $(NAME)!)

fclean: clean
	$(RM) $(NAME)
	$(call log,WARNING,deleted $(NAME)!)

re: fclean $(NAME)

.PHONY: all bonus clean fclean re

-include $(DEPS)

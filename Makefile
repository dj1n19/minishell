# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lolemmen <lolemmen@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/22 21:44:14 by lolemmen          #+#    #+#              #
#    Updated: 2022/12/23 16:13:49 by lolemmen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean re fclean all
.SILENT:

NAME = minishell

# Compilation

RM = rm -rf
CC = gcc
FLAGS = -Wall -Wextra -Werror
DEBUG = -fsanitize=address -g

# Directories

SRCSDIR = Srcs
INCSDIR = Includes
OBJSDIR = Objs
LIBSDIR = Libft
# LEAKSDIR = Leaks

# Sources

SRC = \
		main.c \
		builtin.c \
		split_cmd.c \
		substitution.c \
		utils.c \
		parsing.c

INC = \
		minishell.h

# **************************************************************************** #

# Special Chars

LOG_CLEAR = \033[2K
LOG_UP = \033[A
LOG_NOCOLOR = \033[0m
LOG_BLACK = \033[1;30m
LOG_RED = \033[1;31m
LOG_GREEN = \033[1;32m
LOG_YELLOW = \033[1;33m
LOG_BLUE = \033[1;34m
LOG_VIOLET = \033[1;35m
LOG_CYAN = \033[1;36m
LOG_WHITE = \033[1;37m

# **************************************************************************** #

SRCS = $(addprefix $(SRCSDIR)/, $(SRC))
OBJS = $(addprefix $(OBJSDIR)/, $(addsuffix .o, $(basename $(SRC))))
OBJS_DIR = $(sort $(dir $(OBJS)))

INCS_DIR = $(addsuffix /, $(INCSDIR))
INCS = $(addprefix -I , $(INCS_DIR))

LIBS_INC = -I $(LIBSDIR)
LIBS_LIB = $(addprefix $(LIBSDIR)/,libft.a)
LIBS_LINK = -L$(LIBSDIR) -lft -lreadline

all : $(NAME) $(LIBS_LIB)

$(NAME) : libs $(OBJS)
	echo "$(LOG_CLEAR)$(NAME)... $(LOG_CYAN)assembling... $(LOG_NOCOLOR)$(LOG_UP)"
	$(CC) $(OBJS) $(LIBS_LINK) -o $(NAME)
	echo "$(LOG_CLEAR)$(NAME)... $(LOG_GREEN)compiled $(LOG_GREEN)✓$(LOG_NOCOLOR)"

libs:
	@make -C $(LIBSDIR)

clean :
	$(RM) $(OBJS_DIR)
	$(RM) $(OBJSDIR)
	make -C $(LIBSDIR) clean
	# make -C $(LEAKSDIR) clean

re : fclean all

fclean : clean
	$(RM) $(NAME)
	make -C $(LIBSDIR) fclean
	# make -C $(LEAKSDIR) fclean

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	mkdir -p $(OBJSDIR) $(OBJS_DIR)
	echo "$(LOG_CLEAR)$(NAME)... $(LOG_YELLOW)$<$(LOG_NOCOLOR)$(LOG_UP)"
	$(CC) -c -o $@ $< $(LIBS_INC) $(INCS) $(FLAGS)

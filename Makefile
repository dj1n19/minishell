CC = gcc

CFLAGS = -Wall -Werror -Wextra

DEBUG = -fsanitize=address -g

NAME = minishell

SRCS =	main.c \
		builtin.c \
		substitution.c \
		utils.c \
		split_cmd.c

OBJS = $(SRCS:.c=.o)

LIB = -Llibft -lft -lreadline

LEAKS = -Lleaks_checker -lleaks

.c.o:
	$(CC) $(CFLAGS) -g -c $< -o $(<:.c=.o)

libft:
	make -C libft/

leaks_checker:	libft
	make -C leaks_checker/

all:	$(NAME)

$(NAME):	libft $(OBJS)
	$(CC) $(CFLAGS) $(LIB) -o $(NAME) $(OBJS)

debug:	libft $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG) $(LIB) -o $(NAME) $(OBJS)

leaks:	leaks_checker $(OBJS)
	$(CC) $(CFLAGS) $(DEBUG) $(LIB) $(LEAKS) -o $(NAME) $(OBJS)

clean:
	make -C libft/ clean
	rm -f $(OBJS)

fclean:		clean
	make -C libft/ fclean
	rm -f $(NAME)

.PHONY:		libft all debug leaks clean fclean
#executor.c is my file.
SRCS = main.c	\
		envp.c	\
		first_split.c	\
		second_split.c	\
		parser.c	\
		parser2.c	\
		utils.c		\
		utils2.c	\
		builtin.c	\
		executor.c	\
		builtin2.c	\
		builtin3.c	\
		exec_1.c	\
		exec_2.c	\
		get_here.c	\
		rm_func.c

NAME = minishell

FLAGS = -Wall -Wextra -Werror -lreadline -g -fsanitize=address
CC = gcc

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): libft $(OBJS)
	@make -C libft
	@$(CC) $(OBJS) libft/libft.a -lreadline -g -fsanitize=address -o $(NAME)

%.o : %.c
	@$(CC) $(FLAGS) -c $^ -o $@

libft:
	@make re -C libft

clean:
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re

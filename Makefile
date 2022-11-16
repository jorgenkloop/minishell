NAME = minishell
FLAGS_TEST = -lreadline -g -fsanitize=address
FLAGS = -Wextra -Wall -Werror -lreadline -g -fsanitize=leak

all: $(NAME)

$(NAME): 
	make -C libft
	gcc *.c libft/libft.a $(FLAGS) -o $(NAME)

libft:
	make re -C libft

clean:
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
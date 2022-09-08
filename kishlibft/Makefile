# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/11 10:48:03 by jnm-jaya          #+#    #+#              #
#    Updated: 2022/03/11 11:57:26 by jnm-jaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_memset.c	\
					ft_bzero.c	\
					ft_memcpy.c	\
					ft_memmove.c	\
					ft_memcmp.c	\
					ft_memchr.c	\
					ft_strlen.c	\
					ft_strlcpy.c	\
					ft_strlcat.c	\
					ft_strchr.c	\
					ft_strrchr.c	\
					ft_strnstr.c	\
					ft_strncmp.c	\
					ft_atoi.c	\
					ft_isalpha.c	\
					ft_isdigit.c	\
					ft_isalnum.c	\
					ft_isascii.c	\
					ft_isprint.c	\
					ft_toupper.c	\
					ft_tolower.c	\
					ft_calloc.c	\
					ft_strdup.c	\
					ft_substr.c	\
					ft_strjoin.c	\
					ft_strtrim.c	\
					ft_split.c	\
					ft_itoa.c	\
					ft_striteri.c	\
					ft_strmapi.c	\
					ft_putchar_fd.c	\
					ft_putstr_fd.c	\
					ft_putendl_fd.c	\
					ft_putnbr_fd.c	\
					ft_printf/ft_printf.c	\
					ft_printf/hex.c	\
					ft_printf/write_add.c	\
					ft_printf/putunbr_ctr.c	\
					get_next_line/ft_gnljoin.c	\
					get_next_line/ft_memstrchr.c	\
					get_next_line/get_next_line.c

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

$(NAME): 
	@gcc -c $(FLAGS) $(SRCS)
	@ar rcs $(NAME) *.o

all : $(NAME)

clean : 
	@rm -f *.o

fclean : clean
	@rm -f $(NAME)

re : fclean all

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:38:20 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/03/11 12:05:35 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 42 

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>

void			ft_bzero(void *s, unsigned int n);
void			ft_putendl_fd(char *s, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));

void			*ft_memset(void *b, int c, unsigned int len);
void			*ft_memcpy(void *dest, const void *src, unsigned int n);
void			*ft_memmove(void *dest, const void *src, unsigned int n);
void			*ft_memchr(const void *str, int c, unsigned int n);
void			*ft_calloc(size_t count, size_t size);

int				ft_memcmp(const void *str1, const void *str2, unsigned int n);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_putnbr_fd(int nb, int fd);
int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
int				ft_printf(const char *format, ...);
int				write_add(void *p);
int				hex(unsigned int x, char format);
int				putunbr_ctr(int n);

unsigned int	ft_strlen(const char *s);
unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);
unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size);

char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_strnstr(const char *s1, const char *s2, unsigned int n);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const  *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_memstrchr(char *s, int c, int flag);
char			*get_next_line(int fd);
char			*ft_gnljoin(char *s1, char *s2);

char			**ft_split(char const *s, char c);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:05:13 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/02/18 12:06:24 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/ft_printf.h"
#include "../libft.h"

//checks the flag that comes after %
int	check(const char format, va_list words)
{
	int	ctr;

	ctr = 0;
	if (format == 'd' || format == 'i')
		ctr = ft_putnbr_fd(va_arg(words, int), 1);
	else if (format == 'u')
		ctr = putunbr_ctr(va_arg(words, unsigned int));
	else if (format == 'p')
		ctr = write_add(va_arg(words, void *));
	else if (format == 'c')
		ctr = ft_putchar_fd(va_arg(words, int), 1);
	else if (format == 's')
		ctr = ft_putstr_fd(va_arg(words, char *), 1);
	else if (format == 'x' || format == 'X')
		ctr = hex(va_arg(words, unsigned int), format);
	else if (format == '%')
	{
		write(1, "%", 1);
		ctr = 1;
	}
	return (ctr);
}

int	ft_printf(const char *format, ...)
{
	va_list	words;
	int		ctr;
	int		add;
	int		flag;

	va_start(words, format);
	ctr = 0;
	add = 0;
	flag = 0;
	while (format[ctr] != '\0')
	{
		if (format[ctr] == '%')
		{
			add = add + check(format[ctr + 1], words);
			ctr++;
			flag++;
		}
		else
			write(1, &format[ctr], 1);
		ctr++;
	}
	if (flag != 0)
		ctr = ctr + add - (flag * 2);
	va_end(words);
	return (ctr);
}

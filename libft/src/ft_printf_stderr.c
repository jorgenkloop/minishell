/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stderr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenglert <aenglert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:49:38 by aenglert          #+#    #+#             */
/*   Updated: 2021/10/28 16:27:31 by aenglert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	sta_ft_uns(
	unsigned long nbr, unsigned int base, char *chars, int *count)
{
	if (nbr >= base)
		sta_ft_uns(nbr / base, base, chars, count);
	*count += ft_putcharret_fd(chars[nbr % base], STDERR_FILENO);
}

static void	static_ft_signed(
	long nbr, unsigned int base, char *chars, int *count)
{
	if (nbr < 0)
	{
		ft_putcharret_fd('-', STDERR_FILENO);
		nbr *= -1;
		sta_ft_uns(nbr, base, chars, count);
		*count += 1;
	}
	else
		sta_ft_uns(nbr, base, chars, count);
}

static int	static_ft_check(char c, va_list *args)
{
	int	count;

	count = 0;
	if (c == '%')
		return (ft_putcharret_fd('%', STDERR_FILENO));
	else if (c == 'c')
		return (ft_putcharret_fd(va_arg(*args, int), STDERR_FILENO));
	else if (c == 's')
		return (ft_putstrret_fd(va_arg(*args, char *), STDERR_FILENO));
	else if (c == 'd' || c == 'i')
		static_ft_signed(va_arg(*args, int), 10, "0123456789", &count);
	else if (c == 'u')
		sta_ft_uns(va_arg(*args, unsigned int), 10, "0123456789", &count);
	else if (c == 'x')
		sta_ft_uns(va_arg(*args, unsigned int), 16, "0123456789abcdef", &count);
	else if (c == 'X')
		sta_ft_uns(va_arg(*args, unsigned int), 16, "0123456789ABCDEF", &count);
	else if (c == 'p')
	{
		ft_putstrret_fd("0x", STDERR_FILENO);
		sta_ft_uns((unsigned long)va_arg(*args, void *),
			16, "0123456789abcdef", &count);
		count += 2;
	}
	return (count);
}

int	ft_printf_stderr(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	va_start(args, format);
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			count += static_ft_check(format[i], &args);
		}
		else
		{
			count += ft_putcharret_fd(format[i], STDERR_FILENO);
		}
		i++;
	}
	va_end(args);
	return (count);
}

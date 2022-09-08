/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/01/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		strlen;
	va_list	arg;
	char	c;

	strlen = 0;
	va_start(arg, str);
	while (*str)
	{
		if (*str != '%')
			ft_printchar(*str, &strlen);
		else
		{
			c = *(str + 1);
			if (ft_partof(c, "csp%diuxX"))
				ft_printspec(c, arg, &strlen);
			str++;
		}
		str++;
	}
	va_end(arg);
	return (strlen);
}
// //uncomment this and then test by typing 'make t'
// #include <stdio.h>

// int	main(void)
// {
// 	ft_printf("ft_printf: Hello World!\n");
// 	printf("printf: Hello World!\n");
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 19:32:36 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/17 14:40:00 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digits(int n)
{
	int	ctr;

	ctr = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		ctr++;
	}
	return (ctr);
}

static int	ft_last(int n)
{
	int	i;

	i = n % 10;
	if (i < 0)
		i *= -1;
	return (i);
}

static char	*ft_conv(char *s, int n, int digits, int flag)
{
	int	i;

	if (flag == 0)
	{
		s[digits] = '\0';
		while (n >= 0 && digits >= 0)
		{
			i = ft_last(n);
			s[digits - 1] = i + '0';
			n = n / 10;
			digits--;
		}
	}
	else
	{
		s[digits + 1] = '\0';
		s[0] = '-';
		while (n != 0)
		{
			i = ft_last(n);
			s[digits--] = i + '0';
			n = n / 10;
		}
	}
	return (s);
}

char	*ft_itoa(int n)
{
	int		digits;
	int		flag;
	char	*s;

	digits = ft_digits(n);
	if (n >= 0)
	{
		s = (char *)malloc(digits + 1);
		flag = 0;
	}
	else
	{
		s = (char *)malloc(digits + 2);
		flag = 1;
	}
	if (!s)
		return (0);
	ft_conv(s, n, digits, flag);
	return (s);
}

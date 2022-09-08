/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:57:21 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/03/04 13:25:21 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	spacing(char *str, int i)
{
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		   	 || str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	num;

	n = 0;
	i = 0;
	num = 0;
	if (str[i] == '\0')
		return (0);
	i = spacing((char *)str, i);
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			n++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = num * 10 + (str[i] - '0');
		else
			return (-1);
		i++;
	}
	if (n % 2 == 0)
		return (num);
	else
		return (-1 * num);
}

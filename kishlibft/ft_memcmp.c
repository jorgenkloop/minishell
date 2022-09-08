/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:21:00 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/11 14:07:22 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, unsigned int n)
{
	unsigned char	*b;
	unsigned char	*c;
	unsigned int	a;

	b = (unsigned char *)str1;
	c = (unsigned char *)str2;
	a = 0;
	while (a < n)
	{
		if (b[a] != c[a])
			return (b[a] - c[a]);
		a++;
	}
	return (0);
}

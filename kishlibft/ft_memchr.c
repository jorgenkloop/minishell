/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:18:07 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/11 14:06:43 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, unsigned int n)
{
	unsigned char	value;
	unsigned char	*check;
	unsigned int	ctr;

	ctr = 0;
	value = (unsigned char)c;
	check = (unsigned char *)str;
	while (ctr < n)
	{
		if (value == check[ctr])
			return (check + ctr);
		if (value != check[ctr] && ctr == n - 1)
			return (0);
		ctr++;
	}
	return (0);
}

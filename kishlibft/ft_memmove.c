/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:19:47 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/14 14:49:22 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, unsigned int n)
{
	unsigned int	ctr;
	unsigned char	*d;
	unsigned char	*c;

	ctr = 0;
	d = (unsigned char *)dest;
	c = (unsigned char *)src;
	if (dest == src)
		return (dest);
	if (c < d)
	{
		while (n-- != 0)
			d[n] = c[n];
		return (dest);
	}
	while (n-- != 0)
	{
		d[ctr] = c[ctr];
		ctr++;
	}
	return (dest);
}

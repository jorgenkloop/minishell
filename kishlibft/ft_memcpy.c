/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:52:50 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/22 16:02:22 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned int	ctr;
	unsigned char	*d;
	unsigned char	*c;

	ctr = 0;
	if (!dest && !src)
		return ((void *)0);
	d = (unsigned char *)dest;
	c = (unsigned char *)src;
	while (ctr < n)
	{
		d[ctr] = c[ctr];
		ctr++;
	}
	return (dest);
}

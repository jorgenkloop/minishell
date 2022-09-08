/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:45:14 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/11 13:48:39 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, unsigned int len)
{
	unsigned int	ctr;
	unsigned char	*d;

	ctr = 0;
	d = (unsigned char *)b;
	while (ctr < len)
	{
		d[ctr] = c;
		ctr++;
	}
	return (d);
}

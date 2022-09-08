/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:21:54 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/11 13:49:45 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, unsigned int n)
{
	unsigned int	ctr;
	unsigned char	*d;

	ctr = 0;
	d = (unsigned char *)s;
	while (ctr < n)
	{
		d[ctr] = '\0';
		ctr++;
	}
}

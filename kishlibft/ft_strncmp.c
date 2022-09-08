/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:51:30 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/11 14:18:41 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	x;
	unsigned char	y;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		x = s1[i];
		y = s2[i];
		if ((x - y) != 0)
			return (x - y);
		i++;
	}
	return (0);
}

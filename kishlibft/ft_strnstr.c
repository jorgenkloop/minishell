/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:31:44 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/15 11:10:55 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	ctr1;
	unsigned int	ctr2;
	unsigned int	len;

	len = ft_strlen(s2);
	ctr1 = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[ctr1] != '\0')
	{
		ctr2 = 0;
		if (s1[ctr1] == s2[ctr2])
		{
			while (s1[ctr1 + ctr2] == s2[ctr2])
			{
				ctr2++;
				if (s2[ctr2] == '\0' && ctr1 + len <= n)
					return ((char *)s1 + ctr1);
			}
		}
		ctr1++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:45:06 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/22 18:19:36 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	a;

	a = 0;
	if (str[0] == c)
		return ((char *) str);
	while (str[a++] != '\0')
	{
		if (str[a] == c)
			return ((char *)str + a);
	}
	return (0);
}

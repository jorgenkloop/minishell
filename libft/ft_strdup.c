/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/10/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
returns copy of s1
*/
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*p;
	int		i;

	i = 0;
	if (!s1)
		return ((char *)ft_calloc(1, 1));
	while (s1[i])
		i++;
	str = (char *)malloc(i + 1);
	if (str == 0)
		return (0);
	p = str;
	while (*s1)
		*p++ = *(unsigned char *)s1++;
	*p = '\0';
	return (str);
}

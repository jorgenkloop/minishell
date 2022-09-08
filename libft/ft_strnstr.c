/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/10/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	char	*n;
	size_t	l;

	if (*needle == 0)
		return ((char *)haystack);
	n = (char *)needle;
	while (*haystack && len > 0)
	{
		h = (char *)haystack;
		l = len;
		while (*haystack && *needle && *haystack == *needle && len-- > 0)
		{
			haystack++;
			needle++;
		}
		if (!*needle)
			return (h);
		haystack = ++h;
		needle = n;
		len = --l;
	}
	return (0);
}
/*
#include <stdio.h>
int     main(void)
{
	char *str = ft_strnstr("Needle in the haystack", "the", 0);
	printf("%s\n", str);
}
*/
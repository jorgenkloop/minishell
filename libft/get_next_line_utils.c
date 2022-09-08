/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/10/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;
	size_t	i;

	if (!s || start >= ft_strlen(s))
		return (ft_strdup(""));
	slen = ft_strlen(s);
	if (slen - start > len)
		substr = malloc(sizeof(char) * len + 1);
	else
		substr = malloc(sizeof(char) * slen - start + 1);
	if (!substr)
		return (0);
	i = 0;
	while (i < len && s[i])
	{
		substr[i] = s[i + start];
		if (s[i + start] == 0)
			return (substr);
		i++;
	}
	substr[i] = 0;
	return (substr);
}

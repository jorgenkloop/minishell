/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:41:36 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/28 15:08:26 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*ptr;

	if (s1[0] == '\0' || set[0] == '\0')
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (check(s1[start], set) == 1)
		start++;
	if (start == end)
		return (ptr = ft_calloc(1, 1));
	while (check(s1[end - 1], set) == 1)
		end--;
	ptr = (char *)malloc(end - start);
	if (!ptr)
		return (0);
	ft_memmove(ptr, s1 + start, end - start);
	ptr[end - start] = '\0';
	return (ptr);
}

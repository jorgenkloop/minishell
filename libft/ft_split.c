/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/10/26 16:38:47 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(const char *s, char c)
{
	int	ctr;
	int	i;

	ctr = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			ctr++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (ctr);
}

static char	*ft_strndup(const char *s, size_t ctr)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * ctr + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, ctr + 1);
	str[ctr] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		end;
	int		start;
	int		x;
	char	**ptr;

	end = 0;
	x = 0;
	ptr = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s[end] != '\0')
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] != '\0' && s[end] != c)
			end++;
		if (end > start)
		{
			ptr[x] = ft_strndup(s + start, end - start);
			x++;
		}
	}
	ptr[x] = NULL;
	return (ptr);
}

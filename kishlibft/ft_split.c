/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:32:47 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/07/06 17:47:28 by jnm-jaya         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:17:28 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/07/02 17:12:35 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	ctr;
	char			*str;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (s)
	{
		if (len > ft_strlen(s) - start)
			len = ft_strlen(s) - start;
		str = (char *)malloc(len + 1);
		if (!str)
			return (0);
		ctr = 0;
		while (ctr < len)
		{
			str[ctr] = s[start];
			ctr++;
			start++;
		}
		str[len] = '\0';
		return (str);
	}
	return (ft_strdup(""));
}

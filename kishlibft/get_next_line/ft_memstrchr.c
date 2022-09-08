/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memstrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:43:14 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/03/11 11:51:30 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_memstrchr(char *s, int c, int flag)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!s)
		return (NULL);
	if (flag == 0)
	{
		while (s[i++])
		{
			if (s[i] == '\n')
				return (s);
		}
	}
	else
	{
		ptr = (char *)malloc(sizeof(char) * (ft_strlen(s) - c + 1));
		c++;
		while (s[c])
			ptr[i++] = s[c++];
		ptr[i] = '\0';
		free(s);
		return (ptr);
	}
	return (0);
}

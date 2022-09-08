/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:26:06 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/15 17:10:35 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		ctr;

	ctr = 0;
	if (!f)
		return (ft_strdup(""));
	else if (!s || (!s && !f))
		return (ft_strdup(s));
	ptr = ft_strdup(s);
	if (!ptr)
		return (0);
	while (s[ctr] != '\0')
	{
		ptr[ctr] = (*f)(ctr, s[ctr]);
		ctr++;
	}
	return (ptr);
}

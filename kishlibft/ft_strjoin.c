/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:31:00 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/11 14:33:42 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*ptr;
	unsigned int	len1;
	unsigned int	len2;

	if (*s1 == '\0' && *s2 == '\0')
		return (ft_strdup(""));
	if (*s1 != '\0' && *s2 == '\0')
		return (ft_strdup(s1));
	if (*s1 == '\0' && *s2 != '\0')
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)malloc(len1 + len2 + 1);
	if (!ptr)
		return (0);
	ft_memmove(ptr, s1, len1);
	ft_memmove(ptr + len1, s2, len2);
	ptr[len1 + len2] = '\0';
	return (ptr);
}

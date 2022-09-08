/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:37:51 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/11 14:31:45 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*ptr;
	unsigned int	len;

	len = ft_strlen(s1) + 1;
	ptr = (char *)malloc(len);
	if (!ptr)
		return (0);
	ptr = ft_memcpy(ptr, s1, len);
	return (ptr);
}

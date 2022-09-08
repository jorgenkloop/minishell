/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 17:37:37 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/06/23 16:01:25 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	int				len;
	unsigned int	offset;
	int				i;

	offset = ft_strlen(dest);
	if (size < offset)
		return (size + ft_strlen(src));
	len = size - offset - 1;
	i = 0;
	while (src[i] != '\0' && i < len)
	{
		dest[offset] = src[i];
		offset++;
		i++;
	}
	dest[offset] = '\0';
	while (src[i] != '\0')
	{
		i++;
		offset++;
	}
	return (offset);
}

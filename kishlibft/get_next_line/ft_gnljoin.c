/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnljoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:31:00 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/03/11 11:42:09 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_gnljoin(char *s1, char *s2)
{
	char			*ptr;
	unsigned int	ctr1;
	unsigned int	ctr2;

	ctr1 = -1;
	ctr2 = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	while (s1[++ctr1])
		ptr[ctr1] = s1[ctr1];
	while (s2[ctr2])
		ptr[ctr1++] = s2[ctr2++];
	ptr[ctr1] = '\0';
	free(s1);
	return (ptr);
}

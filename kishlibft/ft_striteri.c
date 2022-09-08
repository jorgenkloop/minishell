/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 10:33:43 by jnm-jaya          #+#    #+#             */
/*   Updated: 2021/07/07 11:33:09 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	ctr;

	ctr = 0;
	if (s != NULL && f != NULL)
	{
		while (s[ctr] != '\0')
		{
			f(ctr, &s[ctr]);
			ctr++;
		}
	}
}

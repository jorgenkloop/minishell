/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:22:29 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/02/18 12:06:47 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	g_uhex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
						'B', 'C', 'D', 'E', 'F'};
char	g_lhex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
						'b', 'c', 'd', 'e', 'f'};

int	hex(unsigned int x, char format)
{
	char			buf[8];
	unsigned long	i;
	int				ctr;

	i = 0;
	ctr = 0;
	if (x == 0)
		return (write(1, "0", 1));
	while (i < (sizeof(x) * 2))
	{
		if ((x >> ((sizeof(x) * 2 - 1 - i) * 4)) < 1)
			i++;
		else
		{
			if (format == 'X')
				buf[ctr++] = g_uhex[(x >> ((sizeof(x) * 2 - 1 - i) * 4)) & 0xf];
			else
				buf[ctr++] = g_lhex[(x >> ((sizeof(x) * 2 - 1 - i) * 4)) & 0xf];
			i++;
		}
	}
	buf[ctr + 1] = '\0';
	return (write(1, buf, ctr));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:05:30 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/02/18 12:07:29 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*g_buf = "0123456789abcdef";

int	write_add(void *p)
{
	unsigned long	x;
	char			address[14];
	size_t			i;
	int				ctr;

	x = (unsigned long) p;
	i = 0;
	ctr = 2;
	address[0] = '0';
	address[1] = 'x';
	if (x == 0)
		return (write(1, "0x0", 3));
	while (i < (sizeof(x) * 2))
	{
		if ((x >> ((sizeof(x) * 2 - 1 - i) * 4)) < 1)
			i++;
		else
		{
			address[ctr++] = g_buf[(x >> ((sizeof(x) * 2 - 1 - i) * 4)) & 0xf];
			i++;
		}
	}
	address[ctr + 1] = '\0';
	return (write(1, address, ctr));
}

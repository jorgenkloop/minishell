/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunbr_ctr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:27:09 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/02/18 12:07:09 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_putnbr2(int n)
{
	char	a;

	a = n + '0';
	write(1, &a, 1);
}

int	putunbr_ctr(int n)
{
	static int	ctr = 0;
	int			temp;

	temp = ctr;
	if (n < 0)
	{
		n *= -1;
		write(1, "-", 1);
		ctr++;
	}
	if (n < 10)
		ft_putnbr2(n);
	else if (n > 0)
	{
		ctr++;
		putunbr_ctr(n / 10);
		putunbr_ctr(n % 10);
	}
	return (ctr + 1 - temp);
}

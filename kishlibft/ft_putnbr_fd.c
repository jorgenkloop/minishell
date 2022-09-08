/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:27:09 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/02/18 12:01:11 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr2(int n, int fd)
{
	char	a;

	a = n + '0';
	write(fd, &a, 1);
}

int	ft_putnbr_fd(int n, int fd)
{
	static int	ctr = 0;
	int			temp;

	temp = ctr;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
		ctr++;
	}
	if (n < 10)
		ft_putnbr2(n, fd);
	else if (n > 0)
	{
		ctr++;
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	return (ctr + 1 - temp);
}

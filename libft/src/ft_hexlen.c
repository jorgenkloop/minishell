/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:44:18 by aenglert          #+#    #+#             */
/*   Updated: 2022/02/21 20:51:52 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_hexlen(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mylibft.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/01/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
i is long given by %x, but converted to unsigned int
strlen is the int result of ft_printf
*/
void	ft_printhexa(unsigned int i, int *strlen)
{
	if (i >= 4294967295)
		ft_printstr("ffffffff", strlen);
	else
		ft_putnbr_base(i, "0123456789abcdef", strlen);
}

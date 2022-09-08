/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/10/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
allocates memory and initializes all bits to zero.
*/
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (p == 0)
		return (p);
	ft_bzero(p, size * count);
	return (p);
}
/*
#include <stdio.h>
int	main(void)
{
	int size = 10;
	char *str = (char *)ft_calloc(size, sizeof(char));
	int i = 0;
	while (i <= size)
	{
		printf("value of str[%d] = %c\n", i, str[i]);
		i++;
	}
	i = 0;
	while (i <= size)
	{
		str[i] = '1';
		printf("value of str[%d] = %c\n", i, str[i]);
		i++;
	}	
}
*/

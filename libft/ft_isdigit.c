/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/10/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
returns 2048 if c represents characters 0 to 9, otherwise returns 0 (checked)
*/
#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	else
		return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int main(void)
{
  int c = '0';
  while (c >= '0' && c <= 'A')
  {
    int res = ft_isdigit(c);
    int res2 = isdigit(c);
    printf("value of ft_isdigit: %d\n", res);
    printf("value of isdigit: %d\n", res2);
    printf("the actual character is %c\n\n", c);
    c++;
  }
}
*/

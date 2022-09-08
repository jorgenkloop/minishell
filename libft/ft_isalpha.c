/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/10/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
returns 1024 if c represents an alphabet, otherwise returns 0
*/
#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1024);
	else
		return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
static void test(int c)
{
	  int res = ft_isalpha(c);
    int res2 = isalpha(c);
    printf("ft_isalpha value is %d\n", res);
    printf("isalpha value is %d\n", res2);
    printf("the actual character is %c\n\n", c);
}
int main(void)
{
  int c;
  c = 'A';
  while (c >= 'A' && c <= 'Z')
		test(c++);
  c = 'a';
  while (c >= 'a' && c <= '~')
		test(c++);
}
*/

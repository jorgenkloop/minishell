/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/10/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
void *memset(void *b, int c, size_t len)
write len bytes of value c (converted to an unsigned char) to the string b.
*/
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = b;
	while (i < len)
		str[i++] = c;
	return (b);
}
/*
#include <stdio.h>
int main(void)
{
  char str[50] = "GeeksForGeeks is for programming geeks.";
  printf("\nBefore ft_memset(): %s\n", str);
  ft_memset(str + 13, '.', 8);
  printf("After ft_memset():  %s\n", str);
  return 0;
}
*/

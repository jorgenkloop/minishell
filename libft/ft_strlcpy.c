/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/10/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//overrides dst with src
//dstsize is maximum length of src -1 (because last character is '/0')
//dstsize must not exceed memory size of dst
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = -1;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (!src)
		return (0);
	while (i++, i < (dstsize - 1) && src[i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int     main(void)
{
char    *str = "abcde";
size_t  len = ft_strlen(str);
char    *str2 = malloc(len);
ft_strlcpy(str2, str, len+1);
printf("result %s\n", str2);
}
*/

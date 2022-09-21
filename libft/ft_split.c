/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/10/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	**error(char **tab)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// 	return (NULL);
// }

// static unsigned int	get_nb_strs(char const *s, char c)
// {
// 	unsigned int	i;
// 	unsigned int	nb_strs;

// 	if (!s[0])
// 		return (0);
// 	i = 0;
// 	nb_strs = 0;
// 	while (s[i] && s[i] == c)
// 		i++;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 		{
// 			nb_strs++;
// 			while (s[i] && s[i] == c)
// 				i++;
// 			continue ;
// 		}
// 		i++;
// 	}
// 	if (s[i - 1] != c)
// 		nb_strs++;
// 	return (nb_strs);
// }

// static void	get_next_str(char **next_str, unsigned int *next_str_len, char c)
// {
// 	unsigned int	i;

// 	*next_str += *next_str_len;
// 	*next_str_len = 0;
// 	i = 0;
// 	while (**next_str && **next_str == c)
// 		(*next_str)++;
// 	while ((*next_str)[i])
// 	{
// 		if ((*next_str)[i] == c)
// 			return ;
// 		(*next_str_len)++;
// 		i++;
// 	}
// }

// char	**ft_split(char const *s, char c)
// {
// 	char			**tab;
// 	char			*next_str;
// 	unsigned int	next_str_len;
// 	unsigned int	nb_strs;
// 	unsigned int	i;

// 	if (!s)
// 		return (0);
// 	nb_strs = get_nb_strs(s, c);
// 	tab = (char **)malloc(sizeof(char *) * (nb_strs + 1));
// 	if (tab == 0)
// 		return (0);
// 	i = -1;
// 	next_str = (char *)s;
// 	next_str_len = 0;
// 	while (i++, i < nb_strs)
// 	{
// 		get_next_str(&next_str, &next_str_len, c);
// 		tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 1));
// 		if (tab[i] == 0)
// 			return (error(tab));
// 		ft_strlcpy(tab[i], next_str, next_str_len + 1);
// 	}

// 	return (tab);
// }

static int	ft_count(const char *s, char c)
{
	int	ctr;
	int	i;

	ctr = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			ctr++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (ctr);
}

static char	*ft_strndup(const char *s, size_t ctr)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * ctr + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, ctr + 1);
	str[ctr] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		end;
	int		start;
	int		x;
	char	**ptr;

	end = 0;
	x = 0;
	ptr = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s[end] != '\0')
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] != '\0' && s[end] != c)
			end++;
		if (end > start)
		{
			ptr[x] = ft_strndup(s + start, end - start);
			x++;
		}
	}
	ptr[x] = NULL;
	return (ptr);
}
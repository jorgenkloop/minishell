/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:24:40 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:24:42 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//removed quotes from the **arg
//i and j must be -1, k must be 0
//called by lexer
// char	**rm_quote(char **arg, int i, int j, int k)
// {
// 	char	*new;
// 	char	c;

// 	while (arg[++i] != NULL)
// 	{
// 		k = 0;
// 		j = -1;
// 		if (arg[i][0] != '\'' && arg[i][0] != '\"')
// 			continue ;
// 		c = arg[i][0];
// 		new = (char *)malloc(sizeof(char) * (ft_strlen(arg[i]) - 1));
// 		while (arg[i][++j] != '\0')
// 		{
// 			if (arg[i][j] == c)
// 				continue ;
// 			new[k] = arg[i][j];
// 			k++;
// 		}
// 		new[k] = '\0';
// 		free(arg[i]);
// 		arg[i] = ft_strdup(new);
// 		free(new);
// 		new = NULL;
// 	}
// 	return (arg);
// }

static int	check_quote(char *input)
{
	char	c;
	int		i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			c = input[i];
			i++;
			break ;
		}
		i++;
	}
	while (input[i] && input[i] != c)
		i++;
	if (!input[i])
		return (-1);
	else
		return (1);
}

char	*rm_quote(char *input, int i, int j, int k)
{
	char	*new;

	if (check_quote(input) == -1)
		return (input);
	new = malloc(sizeof(char) * ft_strlen(input));
	while (input[++i] != '\0')
	{
		if (k == -1 && (input[i] == '\'' || input[i] == '\"'))
		{
			k = i;
			i++;
		}
		if (k != -1 && input[i] == input[k])
			i++;
		if (input[i])
			new[j] = input[i];
		else
			break ;
		j++;
	}
	new[j] = '\0';
	free(input);
	return (new);
}

static int	skip_space(char *s, int i)
{
	i++;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

//removes whitespace in a string
//c and k must be 0, i must be -1
//called by main
char	*rm_whitespace(char *s, char c, int k, int i)
{
	char	*new;

	new = (char *)ft_calloc(ft_strlen(s) + 2, sizeof(char));
	while (s[++i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (c == 0)
				c = s[i];
			else
				c = 0;
		}
		if (c == 0 && s[i] == ' ')
		{
			i = skip_space(s, i);
			if (s[i] == '\0')
				break ;
			i--;
		}
		new[k] = s[i];
		k++;
	}
	new[k] = '\0';
	free(s);
	return (new);
}

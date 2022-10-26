/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:24:51 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:24:52 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//extracts the string before < > | 
//eg: string is hello<hi, hello is returned
static char	*ex_char_3(char *new, char *s, int x)
{
	int	i;
	int	len;
	int	y;

	i = 0;
	len = 0;
	y = x;
	while (s[y] != '\0' && s[y] != '<' && s[y] != '>' && s[y] != '|')
	{
		len++;
		y++;
	}
	new = (char *)malloc(sizeof(char) * (len + 2));
	while (s[x] != '\0' && s[x] != '<' && s[x] != '>' && s[x] != '|')
	{
		new[i] = s[x];
		i++;
		x++;
	}
	new[i] = '\0';
	return (new);
}

//allocates < > | into their own arrays
static char	*ex_char_2(char *new, char *s, int x)
{
	int	i;

	i = 0;
	new = (char *)malloc(sizeof(char) * 3);
	new[i] = s[x];
	if ((s[x] == '>' || s[x] == '<') && s[x + 1] == s[x])
		new[++i] = s[x + 1];
	new[++i] = '\0';
	return (new);
}

//looks for < > | and passes them to the relevant functions
static char	**ex_char(char **new, char *s, int *y)
{
	int	x;

	x = -1;
	while (s[++x] != '\0')
	{
		if (s[x] == '<' || s[x] == '>' || s[x] == '|')
		{
			new[(*y)] = ex_char_2(new[(*y)], s, x);
			if ((s[x] == '>' || s[x] == '<') && s[x + 1] == s[x])
				x++;
		}
		else
		{
			new[(*y)] = ex_char_3(new[(*y)], s, x);
			x = x + (ft_strlen(new[(*y)]) - 1);
		}
		(*y)++;
	}
	return (new);
}

//further splits when < > | << >> characters are found
char	**split_char(char **arg, int len, int i, int x)
{
	char	**new;
	int		j;

	new = (char **)ft_calloc(len, sizeof(char *));
	while (arg[++i] != NULL)
	{
		j = -1;
		while (arg[i][++j] != '\0')
		{
			if (arg[i][0] == '\'' || arg[i][0] == '\"')
			{
				new[x++] = ft_strdup(arg[i]);
				break ;
			}
			else if (arg[i][j] == '<' || arg[i][j] == '>' || arg[i][j] == '|')
			{
				new = ex_char(new, arg[i], &x);
				break ;
			}
			else if (arg[i][j + 1] == '\0')
				new[x++] = ft_strdup(arg[i]);
		}
	}
	freess(arg);
	return (new);
}

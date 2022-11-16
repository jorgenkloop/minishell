/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:22:09 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:22:11 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//called by cmd_split. extracts the substrings from command and returns it
static char	*ex_str(char *arg, int i, int *j, int flag)
{
	char	*s;
	int		str_len;
	int		k;

	k = 0;
	str_len = (i - (*j)) + 2;
	s = (char *)malloc(str_len * sizeof(char));
	while ((*j) <= i)
	{
		s[k] = arg[(*j)];
		k++;
		(*j)++;
	}
	s[k] = '\0';
	if (flag == 1)
		(*j)++;
	return (s);
}

//called by cmd_split. iterates a string until flag
//is found then return the position of the flag
int	iter_arg(char *arg, int i, int flag)
{
	i++;
	while (arg[i] && arg[i] != flag)
		i++;
	if (!arg[i])
		return (i);
	else
		return (i + 1);
}

static char	**cmd_split(char *arg, int len, int j, int k)
{
	char	**cmd;
	int		i;

	i = -1;
	cmd = (char **)ft_calloc(len + 1, sizeof(char *));
	while (arg[++i] != '\0')
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			i = iter_arg(arg, i, arg[i]);
		if (arg[i] == ' ')
			cmd[k++] = ex_str(arg, i - 1, &j, 1);
	}
	cmd[k] = ex_str(arg, i - 1, &j, 0);
	return (cmd);
}

//the main lexer function
char	**lexer(char **envp, char *s)
{
	char	**input;
	int		ctr[2];
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	ctr[0] = find_len(s, ' ') + 1;
	input = cmd_split(s, ctr[0], 0, 0);
	free(s);
	input = exp_env(input, envp, ctr[0]);
	ctr[1] = find_ctr(input);
	if (ctr[1] > 0)
		input = split_char(input, (ctr[1] * 2) + ctr[0], -1, 0);
	while (input[++i] != NULL)
		input[i] = rm_quote(input[i], -1, 0, -1);
	return (input);
}

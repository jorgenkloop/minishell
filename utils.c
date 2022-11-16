/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:25:13 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:25:15 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//called by main. finds how many arrays are required to be malloced
int	find_len(char *arg, char s)
{
	char	c;
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (arg[++i] != '\0')
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			c = arg[i];
			if (i != 0 && arg[i - 1] && arg[i - 1] != ' ')
				len++;
			while (arg[++i] && arg[i] != c)
				;
			len++;
			if (arg[i + 1] != '\0')
				i++;
			if (i != 0 && arg[i + 1] && arg[i + 1] != ' ')
				len++;
		}
		else if (arg[i] == s || arg[i] == '|')
			len++;
	}
	return (len);
}

//called by main, finds how many <, >, >>, <<, | there are
int	find_ctr(char **arg)
{
	int	i;
	int	j;
	int	ctr;

	i = -1;
	ctr = 0;
	while (arg[++i] != NULL)
	{
		if (arg[i][0] == '\'' || arg[i][0] == '\"')
			continue ;
		j = -1;
		while (arg[i][++j] != '\0')
		{
			if (arg[i][j] == '|' || arg[i][j] == '>' || arg[i][j] == '<')
			{
				ctr++;
				if ((arg[i][j] == '<' || arg[i][j] == '>')
					&& arg[i][j] == arg[i][j + 1])
					j++;
			}
		}
	}
	if (ctr == 1)
		ctr = 3;
	return (ctr);
}

//frees a double char
void	freess(char **ss)
{
	char	**ptr;

	ptr = ss;
	while (*ptr != 0)
	{
		free(*ptr);
		ptr++;
	}
	free(ss);
}

//duplicates a matrix WITHOUT freeing the old one
char	**dup_matrix(char **old)
{
	char	**new;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (old[len] != NULL)
		len++;
	new = (char **)ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

//frees the old, allocates it with new and frees new if flag is 1
char	*free_and_alloc(char *old, char *new, int flag, int end)
{
	char	*s;
	int		i;

	if (flag == 1)
	{
		free(old);
		old = ft_strdup(new);
		free(new);
	}
	else
	{
		i = -1;
		s = malloc(sizeof(char) * ft_strlen(old));
		while (++i < end && old[i] != '$')
			s[i] = old[i];
		if (old[end] != '\0' && old[end + 1] != '\0')
			while (old[end + 1] != '\0')
				s[i++] = old[++end];
		s[i] = '\0';
		free(old);
		old = ft_strdup(s);
		free(s);
	}
	return (old);
}

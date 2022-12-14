/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:21:34 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:21:35 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//called by exp_env, checks for $ sign and returns 
//the position of the start and end
static int	*check_dollar(char *arg, int *pos, int ctr)
{
	int	i;
	int	x[2];

	i = -1;
	x[0] = -1;
	x[1] = -1;
	while (arg[++i] != '\0')
	{
		if (arg[i] == '\'' && ctr != 1)
			i = iter_arg(arg, i, arg[i]);
		if (arg[i] == '$')
		{
			if (i != 0 && arg[i - 1] == '\"')
				x[0] = i - 1;
			else
				x[0] = i;
			x[1] = find_end(arg, i);
			break ;
		}
		if (arg[i] == '\"')
			ctr++;
	}
	pos = x;
	return (pos);
}

//called by get_env. extracts the variable from env and returns it
static char	*repl_env(char **env, char *var)
{
	char	*s;
	char	*name;
	int		i;

	i = -1;
	name = NULL;
	while (env[++i] != NULL)
	{
		if (ft_strlen(var) == 1 && !ft_strncmp(var, "?", 1))
		{
			name = ft_itoa(g_status);
			return (name);
		}
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
		{
			s = ft_strchr(env[i], '=') + 1;
			name = ft_strdup(s);
			break ;
		}
	}
	return (name);
}

//called by exp_env. returns the variable name, etc if 
//$USER is called jnm-jaya is returned
char	*get_env(char *arg, char **env, int *pos)
{
	char	*var;
	char	*name;
	int		i;
	int		a;
	int		b;

	i = 0;
	a = pos[0];
	b = pos[1];
	if (arg[a] == '$')
		a++;
	else if (arg[a] == '\"')
		a += 2;
	var = (char *)malloc(sizeof(char) * ((b - a) + 2));
	while (a <= b)
	{
		var[i] = arg[a];
		a++;
		i++;
	}
	var[i] = '\0';
	name = repl_env(env, var);
	free(var);
	return (name);
}

//called by exp_env. a new char * is allocated 
//and returned with the env variable expanded
static char	*ft_realloc_char(char *old, char *s, int x, int len)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	k = -1;
	new = (char *)malloc(sizeof(char) * (ft_strlen(old) + ft_strlen(s)));
	while (++k < (int)ft_strlen(old) && old[k] != '\0')
	{
		if (k == x)
		{
			while (s[++j] != '\0')
				new[i++] = s[j];
			k = k + len + 1;
		}
		if (k <= (int)ft_strlen(old) && old[k])
			new[i++] = old[k];
	}
	new[i] = '\0';
	free(s);
	return (new);
}

//called by lexer. expands the env variable if 
//it exists otherwise null is returned
char	**exp_env(char **arg, char **env, int len)
{
	char	*var;
	char	*new;
	int		i;
	int		*pos;
	int		pos2[2];

	i = -1;
	while (++i < len && arg[i])
	{
		pos = check_dollar(arg[i], pos, 0);
		if (pos[1] - pos[0] > 1 && pos[0] >= 0 && pos[1] > 0)
		{
			pos2[0] = pos[0];
			pos2[1] = pos[1];
			var = get_env(arg[i], env, pos);
			if (var == NULL)
			{
				arg[i] = free_and_alloc(arg[i], "", 0, pos2[1]);
				continue ;
			}
			new = ft_realloc_char(arg[i], var, pos2[0], pos2[1] - pos2[0]);
			arg[i] = free_and_alloc(arg[i], new, 1, 0);
		}
	}
	return (arg);
}

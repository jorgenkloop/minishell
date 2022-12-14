/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:20:59 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:21:01 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//joins 2 strings with only a \n separating them
char	*ft_strjoin_n(char const *s1, char const *s2)
{
	char	*newstr;
	int		s1_len;
	int		s2_len;

	if (!(s1) && !(s2))
		return (0);
	else if (s1 == 0)
		return (ft_strdup(s2));
	else if (s2 == 0)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (newstr == 0)
		return (0);
	ft_strlcpy(newstr, s1, s1_len + 1);
	newstr[s1_len] = '\n';
	ft_strlcat(newstr + (s1_len + 1), s2, s2_len + 1);
	return (newstr);
}

void	run_env(t_data data)
{
	int	i;
	int	fd;

	if (data.cmd->args != NULL && data.cmd->args->s[0] != '\0')
	{
		mini_perror("Please run without options or arguments\n", 1, 1);
		return ;
	}
	i = -1;
	fd = 1;
	while (data.envp[++i] != NULL)
		ft_putendl_fd(data.envp[i], fd);
	g_status = 0;
}

char	**edit_envp(char **envp, char *var, char *str)
{
	char	*new;
	int		len;
	int		i;

	i = -1;
	len = 0;
	new = ft_strjoin(var, str);
	if (str[0] != '\0')
		len = ft_strlen(var);
	else
	{
		while (var[len] != '=')
			len++;
		len++;
	}
	while (envp[++i] != NULL)
	{
		if (!(ft_strncmp(envp[i], var, len)))
		{
			free(envp[i]);
			envp[i] = ft_strdup(new);
		}
	}
	free(new);
	return (envp);
}

void	run_cd(t_cmd *c, char ***envp, int flag)
{
	char	*s;
	char	*pwd;
	int		pos[2];

	if (!c->args || (c->args && !ft_strcmp_n(c->args->s, "~", 1)))
	{
		pos[0] = 0;
		pos[1] = 4;
		s = get_env("$HOME", *envp, pos);
		flag = 1;
	}
	else
		s = c->args->s;
	pwd = getcwd(NULL, 0);
	*envp = edit_envp(*envp, "OLDPWD=", pwd);
	if (chdir(s) < 0)
		mini_perror("No such file or directory\n", 1, 0);
	free(pwd);
	pwd = getcwd(NULL, 0);
	*envp = edit_envp(*envp, "PWD=", pwd);
	free(pwd);
	pwd = NULL;
	if (flag == 1)
		free(s);
}

void	run_exit(t_data data, int i)
{
	t_cmd	*cmd;
	int		status;

	cmd = data.cmd;
	if (cmd->args == NULL)
		exit(1);
	if (cmd->args->next != NULL)
	{
		while (cmd->args->s[++i] != '\0')
		{
			if (cmd->args->s[i] < 48 || cmd->args->s[i] > 57)
				mini_perror("exit: numeric arg required\n", 2, 1);
			if (cmd->args->s[i + 1] == '\0')
				return (mini_perror("exit: too many arguments\n", 2, 0));
		}
	}
	if (cmd->args && !cmd->args->next)
	{
		while (cmd->args->s[++i] != '\0')
			if (cmd->args->s[i] < 48 || cmd->args->s[i] > 57)
				mini_perror("exit: numeric arg required\n", 2, 1);
	}
	status = ft_atoi(cmd->args->s);
	exit(status);
}

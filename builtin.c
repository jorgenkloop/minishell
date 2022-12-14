/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:20:30 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:20:36 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	run_pwd(t_data data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		mini_perror("Error getting current working directory\n", 1, 1);
		return ;
	}
	ft_putendl_fd(pwd, data.cmd->outfile);
	free(pwd);
	g_status = 0;
}

static int	option_check(t_list *args)
{
	t_list	*arg;
	int		i;

	i = 0;
	arg = args;
	if (arg == NULL)
		return (0);
	while (arg->s[0] == '\0')
	{
		arg = arg->next;
		i++;
	}
	if (arg != NULL && arg->s[0] == '-' && arg->s[1] == 'n' && (arg->next))
		return (i + 1);
	else if (arg != NULL && arg->s[0] == '-'
		&& arg->s[1] == 'n' && !(arg->next))
		return (-1);
	else
		return (0);
}

int	run_echo(t_data data, int fd, int i, int j)
{
	t_list	*arg;

	arg = data.cmd->args;
	if (arg == NULL)
		return (write(fd, "\n", 1));
	i = option_check(arg);
	while (arg != NULL && i != -1)
	{
		if (i > 0)
			while (++j < i)
				arg = arg->next;
		ft_putstr_fd(arg->s, fd);
		if (arg->next != NULL && arg->s[0] != '\0')
			write(fd, " ", 1);
		else if (arg->next == NULL && i > 0)
			write(fd, "\0", 1);
		else if (arg->next == NULL && i == 0)
			write(fd, "\n", 1);
		arg = arg->next;
	}
	if (data.cmd->stout_redir != NULL)
		close(fd);
	return (0);
}

//checks if there is any input after redirects
int	check_redirect(t_data data)
{
	char	c;
	int		i;
	int		len;

	i = -1;
	while (data.cmd->full[++i] != NULL)
	{
		if (data.cmd->full[i][0] == '<' || data.cmd->full[i][0] == '>')
		{
			c = data.cmd->full[i][0];
			len = ft_strlen(data.cmd->full[i]);
			if (!data.cmd->full[i + 1]
				&& ((len == 2 && data.cmd->full[i][1] == c) || len == 1))
			{
				mini_perror("Syntax err near unex token `newline\'\n", 2, 0);
				return (-1);
			}
		}
	}
	return (0);
}

t_data	builtin(t_data data)
{
	int		c;
	int		i;

	c = check_redirect(data);
	if (c != -1 && data.cmd->exe && data.cmd->next == NULL
		&& !(ft_strcmp_n(data.cmd->exe->s, "cd", 2)))
		run_cd(data.cmd, &(data.envp), 0);
	else if (c != -1 && data.cmd->exe && data.cmd->next == NULL
		&& !(ft_strcmp_n(data.cmd->exe->s, "export", 6)))
		run_export(data.cmd, &(data.envp), 0, 0);
	else if (c != -1 && data.cmd->exe && data.cmd->next == NULL
		&& !(ft_strcmp_n(data.cmd->exe->s, "unset", 5)))
		run_unset(data.cmd, &(data.envp));
	else if (c != -1 && data.cmd->exe && data.cmd->next == NULL
		&& !(ft_strcmp_n(data.cmd->exe->s, "exit", 4)))
		run_exit(data, -1);
	else if (c != -1)
	{
		i = exec_fork(data, 0, 0, 0);
		parent_wait(data, i);
	}
	freedata(data);
	return (data);
}

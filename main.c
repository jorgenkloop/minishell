/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:23:52 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:23:55 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	g_status;

t_list	*ret_free_list(t_list *list)
{
	t_list	*temp;

	temp = list;
	list = list->next;
	free(temp->s);
	free(temp);
	return (list);
}

void	ft_freelist(t_list *list)
{
	t_list	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp->s);
		free(temp);
	}
}

void	freedata(t_data data)
{
	t_cmd	*temp;

	while (data.cmd != NULL)
	{
		temp = data.cmd->next;
		freess(data.cmd->full);
		ft_freelist(data.cmd->exe);
		ft_freelist(data.cmd->args);
		ft_freelist(data.cmd->stdin_redir);
		ft_freelist(data.cmd->stout_redir);
		free(data.cmd);
		data.cmd = temp;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	char	**input;
	char	*s;

	if (argv [1] != NULL && argc != 1)
		return (0);
	g_status = 0;
	data.envp = dup_matrix(envp);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, siginthandler);
		s = get_readline();
		if (s == NULL)
			continue ;
		input = lexer(data.envp, s);
		data.cmd = parse(input);
		data = builtin(data);
		freess(input);
		input = NULL;
		data.cmd = NULL;
	}
	free(s);
	freess(data.envp);
	return (0);
}

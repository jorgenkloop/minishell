#include "libft/libft.h"
#include "minishell.h"

int	num_cmd(t_data data)
{
	int		i;

	i = 0;
	while (data.cmd != NULL)
	{
		data.cmd = data.cmd->next;
		i++;
	}
	return (i);
}

void	close_exit(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	return (mini_perror("Error with fork\n", 1, 0));
}

static void	stdout_file(t_data data)
{
	char	*s;
	int		i;

	s = data.cmd->stout_redir->s;
	i = 0;
	while (s[i] == '>' || s[i] == ' ')
		i++;
	if (s[0] == '>' && s[1] == '>')
		open(s + i, O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (s[0] == '>' && s[1] != '>')
		open(s + i, O_CREAT | O_WRONLY | O_TRUNC, 0777);
}

//for the case of multiple redirections in a single command
t_data	check_in_out(t_data data)
{
	t_list	*tmpin;
	t_list	*tmpout;

	while (data.cmd->stdin_redir && data.cmd->stdin_redir->next)
	{
		tmpin = data.cmd->stdin_redir;
		data.cmd->stdin_redir = ret_free_list(tmpin);
	}
	if (data.cmd->stout_redir && data.cmd->stout_redir->next)
	{
		while (data.cmd->stout_redir->next != NULL)
		{
			tmpout = data.cmd->stout_redir;
			stdout_file(data);
			data.cmd->stout_redir = ret_free_list(tmpout);
		}
	}
	return (data);
}

t_data	parent_fd(t_data data, int fd[2], int infilepresent)
{
	int	status;

	if (infilepresent)
	{
        waitpid(-1, &status, 0);
		if (status >= 256 || status == 0)
			g_status = status / 256;
	}
	close(fd[1]);
	if (data.cmd && data.cmd->next != NULL && data.cmd->next->stdin_redir == NULL)
		data.cmd->next->infile = fd[0];
	else
		close(fd[0]);
	if (data.cmd && data.cmd->infile > 2)
		close(data.cmd->infile);
	if (data.cmd && data.cmd->outfile > 2)
		close(data.cmd->outfile);
	return (data);
}

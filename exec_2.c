#include "minishell.h"
#include "libft/libft.h"

int	get_fd(t_data data, int oldfd, int fd, char *s)
{
	int	i;

	if (data.cmd->stdin_redir != NULL && data.cmd->stout_redir != NULL
		&& oldfd < 1)
		s = data.cmd->stdin_redir->s;
	else if (data.cmd->stout_redir != NULL)
		s = data.cmd->stout_redir->s;
	else if (data.cmd->stdin_redir != NULL)
		s = data.cmd->stdin_redir->s;
	else if (data.cmd->stdin_redir == NULL && data.cmd->stout_redir == NULL)
		return (oldfd);
	i = 0;
	while (s[i] == '>' || s[i] == ' ' || s[i] == '<')
		i++;
	if (s[0] == '>' && s[1] == '>')
		fd = open(s + i, O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (s[0] == '>' && s[1] != '>')
		fd = open(s + i, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (s[0] == '<' && s[1] != '<')
		fd = open(s + 1, O_RDONLY);
	else if (s[0] == '<' && s[1] == '<')
		fd = get_here_doc(s + i);
	if (fd < 0)
		mini_perror("Error when opening file\n", 2, 1);
	return (fd);
}

int	is_builtin(t_data data)
{
	t_cmd	*cmd;

	cmd = data.cmd;
	if (!(ft_strncmp(cmd->exe->s, "echo", 4)))
		return (1);
	else if (!(ft_strncmp(cmd->exe->s, "cd", 2)))
		return (1);
	else if (!(ft_strncmp(cmd->exe->s, "pwd", 3)))
		return (1);
	else if (!(ft_strncmp(cmd->exe->s, "env", 3)))
		return (1);
	else if (!(ft_strncmp(cmd->exe->s, "export", 6)))
		return (1);
	else if (!(ft_strncmp(cmd->exe->s, "unset", 5)))
		return (1);
	else if (!(ft_strncmp(cmd->exe->s, "exit", 4)))
		return (1);
	return (0);
}

static void	child_redirect(t_data data, int fd[2])
{
	if (data.cmd->infile != STDIN_FILENO || data.cmd->stdin_redir != NULL)
	{
		data.cmd->infile = get_fd(data, data.cmd->infile, 0, NULL);
		if (dup2(data.cmd->infile, STDIN_FILENO) < 0)
			mini_perror("Error with dup2 command\n", 126, 1);
		close(data.cmd->infile);
	}
	if (data.cmd->stout_redir != NULL)
	{
		data.cmd->outfile = get_fd(data, data.cmd->outfile, 0, NULL);
		if (dup2(data.cmd->outfile, STDOUT_FILENO) < 0)
			mini_perror("Error with dup2 command\n", 126, 1);
	}
	else if (data.cmd->next != NULL)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			mini_perror("Error with dup2 command\n", 126, 1);
	}
	close(fd[1]);
}

static void	child_builtin(t_data data)
{
	if (is_builtin(data) == 0)
		exec_loop(data);
	else if (is_builtin(data) == 1
		&& !(ft_strncmp(data.cmd->exe->s, "echo", 4)))
		g_status = run_echo(data, data.cmd->outfile, 0, -1);
	else if (is_builtin(data) == 1 && !(ft_strncmp(data.cmd->exe->s, "pwd", 3)))
		run_pwd(data);
	else if (is_builtin(data) == 1 && !(ft_strncmp(data.cmd->exe->s, "env", 3)))
		run_env(data);
}

void	child_process(t_data data, int fd[2])
{
	child_redirect(data, fd);
	close(fd[0]);
	child_builtin(data);
	exit(g_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:21:43 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:21:47 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//obtain the correct argv for execve
char	**exec_arg(t_data data)
{
	int	i;

	i = 0;
	if (data.cmd->stdin_redir == NULL && data.cmd->stout_redir == NULL)
		return (data.cmd->full);
	while (data.cmd->full[i] != NULL)
	{
		if (data.cmd->full[i][0] == '>' || data.cmd->full[i][0] == '<')
		{
			while (data.cmd->full[i] != NULL)
			{
				free(data.cmd->full[i]);
				data.cmd->full[i] = NULL;
				i++;
			}
			return (data.cmd->full);
		}
		i++;
	}
	return (data.cmd->full);
}

//gets the path variable and splits them 
//by ':', returns the dir based on the index
char	*iter_dir(t_data data, int index, char *s)
{
	char	*path;
	char	**env;
	char	*full;
	int		pos[2];

	pos[0] = 0;
	pos[1] = 4;
	path = get_env("$PATH", data.envp, pos);
	if (path == NULL)
		mini_perror("Error accessing path variable\n", 1, 1);
	env = ft_split(path, ':');
	free(path);
	path = NULL;
	full = NULL;
	s = env[index];
	if (ft_strlen(s) > 0 && s[ft_strlen(s) - 1] == '/')
		full = ft_strjoin(s, data.cmd->exe->s);
	else if (s && data.cmd->exe->s)
	{
		path = ft_strjoin(s, "/");
		full = ft_strjoin(path, data.cmd->exe->s);
		free(path);
	}
	freess(env);
	return (full);
}

//the main execution function. loops through each dir 
//until execve executes using the correct dir
void	exec_loop(t_data data)
{
	char	*dir;
	char	**s;
	char	*i;
	int		index;

	index = 0;
	i = NULL;
	if (data.cmd->stout_redir != NULL)
	{
		if (dup2(data.cmd->outfile, STDOUT_FILENO) < 0)
			return ;
		close(data.cmd->outfile);
	}
	s = exec_arg(data);
	execve(data.cmd->exe->s, s, data.envp);
	dir = iter_dir(data, index, i);
	while (dir)
	{
		execve(dir, s, data.envp);
		free(dir);
		dir = NULL;
		dir = iter_dir(data, ++index, i);
	}
	if (data.cmd->exe->s[0] != '\0')
		g_status = 127;
}

//the main forking function. child process is sent to func child_process
//main process waits for a change in child process status
// int	exec_fork(t_data data, int i, int pid, int tmpfd)
// {
// 	t_list	*temp;
// 	int		fd[2];
// 	int		num;

// 	num = num_cmd(data);
// 	while (data.cmd != NULL)
// 	{
// 		i++;
// 		data = find_heredoc(data);
// 		data = check_in_out(data);
// 		if (i != num && pipe(fd) < 0)
// 		{
// 			mini_perror("Error with pipe\n", 1, 0);
// 			break ;
// 		}
// 		pid = fork();
// 		if (pid < 0)
// 			close_exit(fd);
// 		else if (pid == 0)
// 			child_process(data, fd, tmpfd, i);
// 		data = parent_fd(data, fd, tmpfd);
// 		data.cmd = data.cmd->next;
// 	}
// 	return (i);
// }

int    exec_fork(t_data data, int i, int pid, int num)
{
    int        fd[2];
    int        infilepresent;

    num = num_cmd(data);
    while (data.cmd != NULL)
    {
        if (data.cmd->stdin_redir != 0)
            infilepresent = 1;
        else
            infilepresent = 0;
        i++;
        data = find_heredoc(data);
        data = check_in_out(data);
        if (i != num && pipe(fd) < 0)
        {
            mini_perror("Error with pipe\n", 1, 0);
            break ;
        }
        pid = fork();
        if (pid < 0)
            close_exit(fd);
        else if (pid == 0)
            child_process(data, fd);
        data = parent_fd(data, fd, infilepresent);
        data.cmd = data.cmd->next;
    }
    return (i);
}

void	parent_wait(t_data data, int i)
{
	int	status;

	while (i != 0)
	{
		waitpid(-1, &status, 0);
		i--;
		if (status >= 256 || status == 0)
			g_status = status / 256;
		if (g_status == 127 && data.cmd->exe->s[0] != '\0')
			mini_perror("Error command not found\n", 127, 0);
	}
}

// void	exec_fork(t_data data, int i, int status, int tmpfd)
// {
// 	t_list	*temp;
// 	int		fd[2];
// 	int		pid;
// 	int		num;

// 	num = num_cmd(data);
// 	while (i <= num)
// 	{
// 		i++;
// 		if (i != num && pipe(fd) < 0)
// 			return (mini_perror("Error with pipe\n", 1, 0));
// 		data = check_in_out(data);
// 		pid = fork();
// 		if (pid < 0)
// 			close_exit(fd);
// 		if (pid == 0)
// 			child_process(data, fd, tmpfd, i);
// 	}
// 	while (i != 0)
// 	{
// 		data = parent_fd(data, fd, tmpfd);
// 		waitpid(-1, &status, 0);
// 		if (status >= 256 || status == 0)
// 			g_status = status / 256;
// 		if (g_status == 127 && data.cmd->exe->s[0] != '\0')
// 			mini_perror("Error command not found\n", 127, 0);
// 		i--;
// 	}
// }

//this function is called for non builtins and if a pipe is detected
// void	check_cmd(t_data data, int tmpfd)
// {
// 	t_list	*out;
// 	int		num;
// 	//int		fd[2];

// 	num = num_cmd(data);
// 	while (1)
// 	{
// 		out = data.cmd->stout_redir;
// 		//if (pipe(fd) < 0)
// 		//	return (mini_perror("Error with pipe\n", 1, 0));
// 		if (data.cmd->exe->s != NULL)
// 			exec_fork(data, num, 0, tmpfd);
// 		//close(fd[1]);
// 		//if (data.cmd->next != NULL && data.cmd->next->stdin_redir == NULL)
// 		//	data.cmd->next->infile = fd[0];
// 		//else
// 		//	close(fd[0]);
// 		// if (data.cmd->infile > 2)
// 		// 	close(data.cmd->infile);
// 		// if (data.cmd->outfile > 2)
// 		// 	close(data.cmd->outfile);

// 		//put in the child process
// 		// if (out == NULL || (out != NULL && out->next == NULL))
// 		// 	break ;
// 		// else if (out != NULL && out->next != NULL)
// 		// 	data.cmd->stout_redir = ret_free_list(out);
// 	}
// }

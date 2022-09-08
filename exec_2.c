#include "minishell.h"
#include "libft/libft.h"

int    is_builtin(t_data data)
{
    t_cmd  *cmd;

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

static void child_redirect(t_data data, int fd[2])
{
    if (data.cmd->infile != STDIN_FILENO || data.cmd->stdin_redir != NULL)
    {
        //printf("in the infile dup\n");
        data.cmd->infile = get_fd(data, data.cmd->infile);
        //printf("infile is %d\n", data.cmd->infile);
        if (dup2(data.cmd->infile, STDIN_FILENO) < 0)
            return;
        close(data.cmd->infile);
    }
    if (data.cmd->stout_redir != NULL)
    {
        //printf("check redirect1\n");
        data.cmd->outfile = get_fd(data, data.cmd->outfile);
        //printf("outfile is %d\n", data.cmd->outfile);
        if (dup2(data.cmd->outfile, STDOUT_FILENO) < 0)
           return;
        //close(data.cmd->outfile);
    }
    else if (data.cmd->next != NULL)
    {
        //printf("check redirect2 fd[1] is %d\n", fd[1]);
        if (dup2(fd[1], STDOUT_FILENO) < 0)
            return;
    }
    close(fd[1]);
    //printf("done redirect\n");
}

static void child_builtin(t_data data)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (is_builtin(data) == 0)
        exec_loop(data);
    else if (is_builtin(data) == 1 && !(ft_strncmp(data.cmd->exe->s, "echo", 4)))
        run_echo(data, data.cmd->outfile, 0, -1);
    else if (is_builtin(data) == 1 && !(ft_strncmp(data.cmd->exe->s, "pwd", 3)))
        run_pwd(data);
    else if (is_builtin(data) == 1 && !(ft_strncmp(data.cmd->exe->s, "env", 3)))
        run_env(data);
}

void    child_process(t_data data, int fd[2])
{
    child_redirect(data, fd);
    close(fd[0]);
    child_builtin(data);
}
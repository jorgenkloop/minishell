#include "minishell.h"
#include "libft/libft.h"

//obtain the correct argv for execve
char    **exec_arg(t_data data)
{
    int i;

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

//gets the path variable and splits them by ':', returns the dir based on the index
char    *iter_dir(t_data data, int index, char *s)
{
    char    *path;
    char    **env;
    char    *full;
    int     pos[2];

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

//the main execution function. loops through each dir until execve executes using the correct dir
void    exec_loop(t_data data)
{
    char    *dir;
    char    **s;
    char    *i;
    int     index;

    index = 0;
    i = NULL;
    if (data.cmd->stout_redir != NULL)
    {
        if (dup2(data.cmd->outfile, STDOUT_FILENO) < 0)
            return;
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

//the main forking function. child process is sent to func child_process, main process waits for a change in child process status
void    exec_fork(t_data data, int fd[2])
{
    t_list  *temp;
    int pid;
    int status;

    while (data.cmd->stdin_redir && data.cmd->stdin_redir->next)
    {
        temp = data.cmd->stdin_redir;
        data.cmd->stdin_redir = ret_free_list(temp);
    }
    pid = fork();
    if (pid < 0)
    {
        close(fd[0]);
        close(fd[1]);
        return (mini_perror("Error with fork\n", 1, 0));
    }
    else if (pid == 0)
        child_process(data, fd);
    else
    {
        waitpid(pid, &status, 0);
        g_status = status/256;
        if (g_status == 127)
           mini_perror("Error command not found\n", 127, 0);
    }
}

//this function is called for non builtins and if a pipe is detected
void   check_cmd(t_data data)
{
    t_list  *out;
    int fd[2];

    while (1)
    {
        out = data.cmd->stout_redir;
        if (pipe(fd) < 0)
            return (mini_perror("Error with pipe\n", 1, 0));
        if (data.cmd->exe->s != NULL)
            exec_fork(data, fd);
        close(fd[1]);
        if (data.cmd->next != NULL && data.cmd->next->stdin_redir == NULL)
            data.cmd->next->infile = fd[0];
        else 
            close(fd[0]);
        if (data.cmd->infile > 2)
            close(data.cmd->infile);
        if (data.cmd->outfile > 2)
            close(data.cmd->outfile);
        if (out == NULL || (out != NULL && out->next == NULL))
            break ;
        else if (out != NULL && out->next != NULL)
            data.cmd->stout_redir = ret_free_list(out);
    }
}
#include "minishell.h"
#include "libft/libft.h"

int get_fd(t_data data, int oldfd)
{
    char    *s;
    int     i;
    int     fd;

    if (data.cmd->stdin_redir != NULL && data.cmd->stout_redir != NULL && oldfd < 1)
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
    else
        fd = oldfd;
    return (fd);
}

void run_pwd(t_data data)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    ft_putendl_fd(pwd, data.cmd->outfile);
    free(pwd);
}

static int  option_check(t_list *args)
{
    t_list  *arg;
    int     i;

    i = 0;
    arg = args;
    while(arg->s[0] == '\0')
    {
        arg = arg->next;
        i++;
    }
    if (arg != NULL && arg->s[0] == '-' && arg->s[1] == 'n')
        return (i + 1);
    else
        return (0);
}

int run_echo(t_data data, int fd, int i, int j)
{
    t_list  *arg;

    arg = data.cmd->args;
    if (arg == NULL || (arg->s[0] == '\0' && arg->next == NULL))
        return (write(fd, "\n", 1));
    i = option_check(arg);
    while (arg != NULL)
    {
        if (i > 0)
            while (++j < i)
                arg = arg->next;
        ft_putstr_fd(arg->s, fd);
        if (arg->next != NULL)
            write(fd, " ", 1);
        else if (arg->next == NULL && i > 0)
            write(fd, "\0", 1);
        else if (arg->next == NULL && i == 0)
            write(fd, "\n", 1);
        arg = arg->next;
    }
    if (data.cmd->stout_redir != NULL)
    {
        //printf("closing fd\n");
        close(fd);
    }
    //printf("done echo\n");
    return (0);
}

t_data    builtin(t_data data)
{
    t_data  aux;

    aux = data;
    while (aux.cmd)
    {
        if (aux.cmd->next == NULL && !(ft_strncmp(aux.cmd->exe->s, "cd", 2)))
            run_cd(aux.cmd, &(aux.envp));
        else if (aux.cmd->next == NULL && !(ft_strncmp(aux.cmd->exe->s, "export", 6)))
            run_export(aux.cmd, &(aux.envp));
        else if (aux.cmd->next == NULL && !(ft_strncmp(aux.cmd->exe->s, "unset", 5)))
            run_unset(aux.cmd, &(aux.envp));
        else if (aux.cmd->next == NULL && !(ft_strncmp(aux.cmd->exe->s, "exit", 4)))
            exit(1);
        else
            check_cmd(aux);
        aux.cmd = aux.cmd->next;
       //printf("done loop\n");
    }
    //printf("exit loop\n");
    return (data);
}
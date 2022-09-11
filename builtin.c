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
    i = -1;
    while (s[++i] == '>' || s[i] == ' ' || s[i] == '<');
    if (s[0] == '>' && s[1] == '>')
        fd = open(s + i, O_CREAT | O_WRONLY | O_APPEND, 0777);
    else if (s[0] == '>' && s[1] != '>')
        fd = open(s + i, O_CREAT | O_WRONLY | O_TRUNC, 0777);
    else if (s[0] == '<' && s[1] != '<')
        fd = open(s + 1, O_RDONLY);
    else if (s[0] == '<' && s[1] == '<')
        fd = get_here_doc(s + i);
    if (fd < 0)
        mini_perror("Error when opening file\n", 2);
    return (fd);
}

void run_pwd(t_data data)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
        mini_perror("Error getting current working directory\n", 1);
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

// t_data    builtin(t_data data)
// {
//     t_data  aux;

//     aux = data;
//     while (aux.cmd)
//     {
//         if (aux.cmd->next == NULL && !(ft_strncmp(aux.cmd->exe->s, "cd", 2)))
//             run_cd(aux.cmd, &(aux.envp));
//         else if (aux.cmd->next == NULL && !(ft_strncmp(aux.cmd->exe->s, "export", 6)))
//             run_export(aux.cmd, &(aux.envp));
//         else if (aux.cmd->next == NULL && !(ft_strncmp(aux.cmd->exe->s, "unset", 5)))
//             run_unset(aux.cmd, &(aux.envp));
//         else if (aux.cmd->next == NULL && !(ft_strncmp(aux.cmd->exe->s, "exit", 4)))
//             exit(1);
//         else
//             check_cmd(aux);
//         aux.cmd = aux.cmd->next;
//        //printf("done loop\n");
//     }
//     //printf("exit loop\n");
//     return (data);
// }

int check_redirect(t_data data)
{
    char    c;
    int     i;
    int     len;

    i = -1;
    while(data.cmd->full[++i] != NULL)
    {
        if (data.cmd->full[i][0] == '<' || data.cmd->full[i][0] == '>')
        {
            c = data.cmd->full[i][0];
            len = ft_strlen(data.cmd->full[i]);
            if ((len == 2 && data.cmd->full[i][1] == c) || len == 1)
            {
                mini_perror("Syntax err near unexpected token `newline\'\n", 2);
                return (-1);
            }
        }
    }
    return (0);
}

void    run_exit(t_data data)
{
    char    *s;
    int     status;

    s = data.cmd->args;
    if (s != NULL && s != NULL)
        mini_perror("exit: too many arguments\n", 2);
    if (s[0] >= 48 && s[0] <= 57)
        exit(2);
    status = ft_atoi(data.cmd->args->s);
    exit(status);
}

t_data    builtin(t_data data)
{
    t_cmd   *temp;
    int     check;

    check = check_redirect(data);
    while (data.cmd)
    {
        if (data.cmd->next == NULL && !(ft_strncmp(data.cmd->exe->s, "cd", 2)) && check != -1)
            run_cd(data.cmd, &(data.envp));
        else if (data.cmd->next == NULL && !(ft_strncmp(data.cmd->exe->s, "export", 6)) && check != -1)
            run_export(data.cmd, &(data.envp));
        else if (data.cmd->next == NULL && !(ft_strncmp(data.cmd->exe->s, "unset", 5)) && check != -1)
            run_unset(data.cmd, &(data.envp));
        else if (data.cmd->next == NULL && !(ft_strncmp(data.cmd->exe->s, "exit", 4)) && check != -1)
            run_exit(data);
        else if (check != -1)
            check_cmd(data);
        temp = data.cmd;
        data.cmd = data.cmd->next;
        freecmd(temp);
    }
    return (data);
}
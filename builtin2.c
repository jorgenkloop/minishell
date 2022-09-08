#include "minishell.h"
#include "libft/libft.h"

//joins 2 strings with only a \n separating them
char *ft_strjoin_n(char const *s1, char const *s2)
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

void run_env(t_data data)
{
    //char    *s;
    int     i;
    int     fd;

    i = -1;
    //s = NULL;
    // if (data.cmd->stout_redir != NULL)
    //     fd = get_fd(data);
    // else if (data.cmd->next != NULL)
    // {
    //     while (data.envp[++i] != NULL)
    //         s = ft_strjoin_n(s, data.envp[i]);
    //     exec_b(data, s);
    //     return;
    // }
    // else
    fd = 1;
    while (data.envp[++i] != NULL)
        ft_putendl_fd(data.envp[i], fd);
}

char    **edit_envp(char **envp, char *var, char *str)
{
    char    *new;
    int     len;
    int     i;

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

void run_cd(t_cmd *command, char ***envp)
{
    char    *s;
    char    *pwd;

    s = command->args->s;
    pwd = getcwd(NULL, 0);
    *envp = edit_envp(*envp, "OLDPWD=", pwd);
    chdir(s);
    free(pwd);
    pwd = getcwd(NULL, 0);
    *envp = edit_envp(*envp, "PWD=", pwd);
    free(pwd);
    pwd = NULL;
}
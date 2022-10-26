#include "minishell.h"
#include "libft/libft.h"

static int	check_env(char **envp, char *s, int flag, int i)
{
	int	j;

	j = -1;
	if (flag == 0)
	{
		while (s[i] != '\0' && s[i] != '=')
			i++;
		if (s[i] == '\0')
			return (-1);
		i++;
	}
	else
		i = ft_strlen(s);
	while (envp[++j] != NULL)
	{
		if (!(ft_strncmp(envp[j], s, i)))
		{
			if (envp[j][i] == '=' && flag == 1)
				return (j);
			else if (flag == 0)
				return (j);
		}
	}
	return (-2);
}

static char	**resize_insert(char *s, char **envp)
{
	char	**new;
	int		i;
	int		len;

	i = 0;
	len = -1;
	while (envp[++len] != NULL);
	new = (char **)ft_calloc(len + 2, sizeof(char *));
	while (envp[i] != NULL)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = ft_strdup(s);
	new[i + 1] = 0;
	freess(envp);
	envp = NULL;
	return (new);
}

static char	**resize_remove(char **envp, int check)
{
	char	**new;
	int		len;
	int		i;
	int		j;
	int		envp_len;

	len = 0;
	i = 0;
	j = 0;
	envp_len = sslen(envp) - 1;
	while (envp[len] != NULL)
		len++;
	new = (char **)ft_calloc(len, sizeof(char *));
	while (envp[i] != NULL && i < envp_len)
	{
		if (i == check)
			i++;
		new[j] = ft_strdup(envp[i]);
		i++;
		j++;
	}
	freess(envp);
	envp = NULL;
	return (new);
}

void	run_unset(t_cmd *command, char ***envp)
{
	t_list	*arg;
	int		check;

	arg = command->args;
	while (arg != NULL)
	{
		check = check_env(*envp, arg->s, 1, 0);
		if (check >= 0)
			*envp = resize_remove(*envp, check);
		arg = arg->next;
	}
	g_status = 0;
}

void	run_export(t_cmd *command, char ***envp)
{
	t_list	*arg;
	int		check;

	arg = command->args;
	while (arg != NULL)
	{
		check = check_env(*envp, arg->s, 0, 0);
		if (check == -1)
			continue ;
		else if (check >= 0)
			*envp = edit_envp(*envp, arg->s, "");
		else if (check == -2)
			*envp = resize_insert(arg->s, *envp);
		arg = arg->next;
	}
	g_status = 0;
}
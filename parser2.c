#include "minishell.h"
#include "libft/libft.h"

size_t	sslen(char **ss)
{
	size_t	len;

	len = 0;
	if (ss == 0)
		return (0);
	while (ss[len] != 0)
	{
		len++;
	}
	return (len);
}

static void	addlist(t_list **list, char *newstr)
{
	t_list	*newlist;
	t_list	*ptr;

	newlist = malloc(sizeof(t_list));
	newlist->s = ft_strdup(newstr);
	newlist->next = 0;
	ptr = *list;
	if (*list == 0)
		*list = newlist;
	else
	{
		while (ptr && ptr->next)
			ptr = ptr->next;
		ptr->next = newlist;
	}
}

void	getoutredir(t_cmd *cmd)
{
	char	*str;
	char	*nextstr;
	char	*joinedstr;
	int		i;

	i = 0;
	while (i < (int)sslen(cmd->full))
	{
		str = cmd->full[i];
		nextstr = cmd->full[i + 1];
		if (!ft_strncmp(">", str, 1) && nextstr != 0)
		{
			joinedstr = ft_strjoin(str, nextstr);
			addlist(&cmd->stout_redir, joinedstr);
			free(joinedstr);
			i = i + 2;
		}
		else
			i++;
	}
}

void	getinredir(t_cmd *cmd)
{
	char	*str;
	char	*nextstr;
	char	*joinedstr;
	int		i;

	i = 0;
	while (i < (int)sslen(cmd->full))
	{
		str = cmd->full[i];
		nextstr = cmd->full[i + 1];
		if (!ft_strncmp("<", str, 1) && nextstr != 0)
		{
			joinedstr = ft_strjoin(str, nextstr);
			addlist(&cmd->stdin_redir, joinedstr);
			free(joinedstr);
			i = i + 2;
		}
		else
			i++;
	}
}

void	getexe(t_cmd *cmd)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = sslen(cmd->full);
	while (i < len)
	{
		str = cmd->full[i];
		if (!ft_strncmp("<", str, 1) || !ft_strncmp(">", str, 1))
			i = i + 2;
		else if (i < len)
		{
			addlist(&cmd->exe, str);
			i++;
			while (i < len && ft_strncmp("<", cmd->full[i], 1)
				&& ft_strncmp(">", cmd->full[i], 1))
			{
				addlist(&cmd->args, cmd->full[i]);
				i++;
			}
		}
	}
}

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

static void addlist(t_list **list, char *newstr)
{
	t_list	*newlist;
	t_list	*ptr;

	newlist = malloc(sizeof(t_list));
	//newlist->s = newstr;
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
	int	i;
	char	*str;
	char	*nextstr;
	char	*joinedstr;
	
	i = 0;
	while (i < (int)sslen(cmd->full))
	{
	 	str = cmd->full[i];
	 	nextstr = cmd->full[i + 1];
		if(!ft_strncmp(">", str, 1) && nextstr != 0)
		{
			joinedstr = ft_strjoin(str, nextstr);
			//printf("joined str for getoutredir = %s\n", joinedstr);
			addlist(&cmd->stout_redir, joinedstr);
			//printf("after joined str for getoutredir = %s\n", &cmd->stout_redir);
			free(joinedstr);
			i = i + 2; 
		}
		else
			i++;
	}
}

void	getinredir(t_cmd *cmd)
{
	int	i;
	char	*str;
	char	*nextstr;
	char	*joinedstr;
	
	i = 0;
	while (i < (int)sslen(cmd->full))
	{
	 	str = cmd->full[i];
	 	nextstr = cmd->full[i + 1];
		if(!ft_strncmp("<", str, 1) && nextstr != 0)
		{
			joinedstr = ft_strjoin(str, nextstr);
			//printf("joined str for getinredir = %s\n", joinedstr);
			addlist(&cmd->stdin_redir, joinedstr);
			//str = ft_strdup(joinedstr);
			//addlist(&cmd->stdin_redir, str);
			//free(str);
			//printf("after joined str for getoutredir = %s\n", &cmd->stdin_redir);
			free(joinedstr);
			i = i + 2; 
		}
		else
			i++;
	}
}

void	getexe(t_cmd *cmd)
{
	int	i;
	char	*str;
	
	i = 0;
	int len = sslen(cmd->full);
	while (i < len)
	{
		str = cmd->full[i];
		if(!ft_strncmp("<", str, 1) || !ft_strncmp(">", str, 1))
		{
			i = i + 2;
		}
		else if (i < len)
		{
			addlist(&cmd->exe, str);
			i++;
			while (i < len && ft_strncmp("<", cmd->full[i], 1) && ft_strncmp(">", cmd->full[i], 1))
			{
				addlist(&cmd->args, cmd->full[i]);
				i++;
			}
		}		
	}
}
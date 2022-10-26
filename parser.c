#include "minishell.h"
#include "libft/libft.h"

static size_t	getpipelen(char **ss)
{
	size_t	len;
	char	**ptr;

	len = 0;
	ptr = ss;
	while (*ptr && ft_strncmp(*ptr, "|", 1))
	{
		len++;
		ptr++;
	}
	return (len);
}

static void	newcmd(t_cmd **cmd)
{
	t_cmd	*newcmd;

	newcmd = malloc(sizeof(t_cmd));
	newcmd->exe = 0;
	newcmd->args = 0;
	newcmd->stdin_redir = 0;
	newcmd->stout_redir = 0;
	newcmd->infile = 0;
	newcmd->outfile = 1;
	(*cmd)->next = newcmd;
	(*cmd) = (*cmd)->next;
}

static void	fillcmd(t_cmd **cmd, char ***ss)
{
	size_t	len;
	size_t	i;

	len = getpipelen(*ss);
	i = 0;
	(*cmd)->full = malloc(sizeof(char *) * (len + 1));
	(*cmd)->full[len] = 0;
	while (i < len)
	{
	 	(*cmd)->full[i] = ft_strdup(*(*ss));
	 	(*ss)++;
	 	i++;
	}
	getinredir(*cmd);
	getoutredir(*cmd);
	getexe(*cmd);
}

t_cmd	*parse(char **ss)
{
	t_cmd	*cmd;
	t_cmd	*ptr;

	cmd = malloc(sizeof(t_cmd) * 1);
	cmd->exe = 0;
	cmd->args = 0;
	cmd->stdin_redir = 0;
	cmd->stout_redir = 0;
	cmd->infile = 0;
	cmd->outfile = 1;
	ptr = cmd;
	while(*ss)
	{
		fillcmd(&ptr, &ss);
		if (*ss != 0 && !ft_strncmp(*ss, "|", 1))
		{
			newcmd(&ptr);
			ss++;
		}
	}
	ptr->next = 0;
	return (cmd);
}

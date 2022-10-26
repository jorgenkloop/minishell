#include "minishell.h"
#include "libft/libft.h"

//called by cmd_split. extracts the substrings from command and returns it 
static char	*ex_str(char *arg, int i, int *j, int flag)
{
	char	*s;
	int		str_len;
	int		k;

	k = 0;
	str_len = (i - (*j)) + 2;
	s = (char *)malloc(str_len * sizeof(char));
	while ((*j) <= i)
	{
		s[k] = arg[(*j)];
		k++;
		(*j)++;
	}
	s[k] = '\0';
	if (flag == 1)
		(*j)++;
	return (s);
}

//called by cmd_split. iterates a string until flag
//is found then return the position of the flag
static int	iter_arg(char *arg, int i, int flag)
{
	i++;
	while (arg[i] != flag)
		i++;
	return (i);
}

//splits argv into an array called input
static char	**cmd_split(char *arg, int len, int j, int k)
{
	char	**cmd;
	int		i;

	i = -1;
	cmd = (char **)ft_calloc(len + 1, sizeof(char *));
	while (arg[++i] != '\0')
	{
		if (arg[i] == ' ')
			cmd[k++] = ex_str(arg, i - 1, &j, 1);
		else if (arg[i] == '\'' || arg[i] == '\"')
		{
			if (i != 0 && arg[i - 1] && arg[i - 1] != ' ')
				cmd[k++] = ex_str(arg, i - 1 , &j, 0);
			i = iter_arg(arg, i, arg[i]);
			cmd[k++] = ex_str(arg, i, &j, 0);
			if (arg[i + 1] == ' ')
				i++;
			j = i + 1;
		}
	}
	cmd[k] = ex_str(arg, i - 1, &j, 0);
	return (cmd);
}

//the main lexer function
char	**lexer(char **envp, char *s)
{
	char	**input;
	int		ctr[2];

	if (!s)
		return (NULL);
	ctr[0] = find_len(s, ' ') + 1;
	input = cmd_split(s, ctr[0], 0, 0);
	free(s);
	input = exp_env(input, envp, ctr[0]);
	ctr[1] = find_ctr(input);
	if (ctr[1] > 0)
		input = split_char(input, (ctr[1] * 2) + ctr[0], -1, 0);
	input = rm_quote(input, -1, 0, -1);
	return (input);    
}

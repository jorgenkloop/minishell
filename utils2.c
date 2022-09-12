#include "minishell.h"
#include "libft/libft.h"

//called by check_dollar to return the end position
int  find_end(char *arg, int i)
{
    while (arg[++i] != '\0')
    {
        if (arg[i] == ' ' || arg[i] == '/')
            return (i);
        else if (arg[i] == '\"')
            return (i);
    }
    return (i);
}

//handles the ctrl-c signal
void	siginthandler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

//checks for whitespace or strings ending with |
//returns the command
static char	*readline_check(char *s, int *flag)
{
	char	*new;
	char	*s2;
	int		len;

	len = ft_strlen(s);
	if (len != 0 && s[len - 1] == '|')
	{
		s2 = readline("> ");
		s2 = rm_whitespace(s2, 0, 0, -1);
		new = ft_strjoin(s, s2);
		free(s2);
		free(s);
		return (new);
	}
	else
		*flag = 1;
	return (s);
}

//obtains the input from terminal
char	*get_readline(void)
{
	char	*s;
	int		flag;

	flag = 0;
	s = readline("input > ");
	if (!s)
		exit(1);
	s = rm_whitespace(s, 0, 0, -1);
	while (1)
	{
		s = readline_check(s, &flag);
		if (flag == 1)
			break ;
	}
	if (s)
		add_history(s);
	else
		exit(1);
	return (s);
}

//prints error message, modifies error code and exits if necessary
void	mini_perror(char *err_str, int err_code, int flag)
{
	ft_putstr_fd(err_str, 2);
	g_status = err_code;
	if (flag == 1)
		exit(g_status);
}
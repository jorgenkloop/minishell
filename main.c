#include "minishell.h"
#include "libft/libft.h"

int g_status;

void	ft_printlist(t_list *list)
{
	t_list *ptr = list;
	while (ptr)
	{
		printf("%s\n", ptr->s);
		ptr = ptr->next;
	}
}

void	printss(char **ss)
{
	char	**ptr;

	ptr = ss;
	while(*ptr != 0)
	{
		printf("%s\n", *ptr);
		ptr++;
	}
	//printf("\n");
}

void	readcmd(t_cmd *cmd)
{
	
	while (cmd !=0)
	{
		printf("\n==READING FROM NODE==\n");
		printf("=full=: \n");
		if (cmd->full !=0)
			printss(cmd->full);
		printf("=exe=: \n");
		if (cmd->exe != 0)
			ft_printlist(cmd->exe);
		printf("=args=: \n");
		if (cmd->args != 0)
			ft_printlist(cmd->args);
		printf("=stdin_redir=: \n");
		if (cmd->stdin_redir != 0)
			ft_printlist(cmd->stdin_redir);
		printf("=stout_redir=: \n");		
		if (cmd->stout_redir != 0)
			ft_printlist(cmd->stout_redir);
		cmd = cmd->next;
	}
}

void	ft_freelist(t_list *list)
{
	t_list	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp->s);
		free(temp);
	}
	// t_list	*ptr;
	
	// if (list != 0)
	// {
	// 	ptr = list->next;
	// 	while (ptr != 0)
	// 	{
	// 		list->next = ptr->next;
	// 		free(ptr->s);
	// 		free(ptr);
	// 		ptr = list->next;
	// 	}
	// 	free(list->s);
	// 	free(list);
	// }
}

void	freecmd(t_cmd *cmd)
{
	t_cmd	*temp;

	//while (cmd != NULL)
	//{
	temp = cmd;
	//cmd = cmd->next;
	freess(temp->full);
	ft_freelist(temp->exe);
	ft_freelist(temp->args);
	ft_freelist(temp->stdin_redir);
	ft_freelist(temp->stout_redir);
	free(temp);
	//}
	// t_cmd *ptr;
	
	// ptr = cmd->next;
	// while (ptr != 0)
	// {
	// 	cmd->next = ptr->next;
	// 	freess(ptr->full);
	// 	ft_freelist(ptr->exe);
	// 	ft_freelist(ptr->args);
	// 	ft_freelist(ptr->stdin_redir);
	// 	ft_freelist(ptr->stout_redir);
	// 	free(ptr);
		
	// 	ptr = cmd->next;
	// }
	// freess(cmd->full);
	// ft_freelist(cmd->exe);
	// ft_freelist(cmd->args);
	// ft_freelist(cmd->stdin_redir);
	// ft_freelist(cmd->stout_redir);
	// free(cmd);
}
// void	freecmd(t_cmd *cmd)
// {
// 	t_cmd *ptr;
	
// 	ptr = cmd->next;
// 	while (ptr != 0)
// 	{
// 		cmd->next = ptr->next;
// 		freess(ptr->full);
// 		ft_freelist(ptr->exe);
// 		ft_freelist(ptr->args);
// 		ft_freelist(ptr->stdin_redir);
// 		ft_freelist(ptr->stout_redir);
// 		free(ptr);
		
// 		ptr = cmd->next;
// 	}
// 	freess(cmd->full);
// 	ft_freelist(cmd->exe);
// 	ft_freelist(cmd->args);
// 	ft_freelist(cmd->stdin_redir);
// 	ft_freelist(cmd->stout_redir);
// 	free(cmd);
// }

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

char	*readline_check(char *s, int *flag)
{
	char	*new;
	char	*s2;
	int		len;

	len = ft_strlen(s);
	if (s[len - 1] == '|')
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

void	mini_perror(char *err_str, int err_code)
{
	ft_putstr_fd(err_str, 2);
	g_status = err_code;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data  data;
	char    **input;
	char    *s;

	if (argv [1] != NULL && argc != 1)
		return (0);
	g_status = 0;
	data.envp = dup_matrix(envp);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, siginthandler);
		s = get_readline();
		input = lexer(data.envp, s);
		if (input == NULL)
			break ;
		data.cmd = parse(input);
		//I will start here.
		data = builtin(data);
		//data = executor(data);
		//readcmd(data.cmd);
		freess(input);
		//freecmd(data.cmd);
		input = NULL;
		data.cmd = NULL;
	}
	free(s);
	freess(data.envp);
	return (0);
}

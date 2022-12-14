/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:24:01 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:24:03 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>
# include "libft/get_next_line.h"

extern int	g_status;

typedef struct s_list
{
	char			*s;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd
{
	char			**full;
	t_list			*exe;
	t_list			*args;
	t_list			*stdin_redir;
	t_list			*stout_redir;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_cmd	*cmd;
	char	**envp;
}	t_data;

t_data	builtin(t_data data);
t_data	check_in_out(t_data data);
t_data	parent_fd(t_data data, int fd[2], int infilepresent);
t_data	find_heredoc(t_data data);

t_cmd	*parse(char **ss);

t_list	*ret_free_list(t_list *list);

char	**dup_matrix(char **old);
char	**exp_env(char **arg, char **env, int len);
char	**split_char(char **arg, int len, int i, int x);
char	**edit_envp(char **envp, char *var, char *str);
char	**lexer(char **envp, char *s);
char	*rm_quote(char *arg, int i, int j, int k);

char	*free_and_alloc(char *old, char *new, int flag, int end);
char	*ft_strjoin_n(char const *s1, char const *s2);
char	*get_env(char *arg, char **env, int *pos);
char	*iter_dir(t_data data, int index, char *s);
char	*rm_whitespace(char *s, char c, int k, int i);
char	*get_readline(void);

int		find_len(char *arg, char s);
int		find_ctr(char **arg);
int		get_fd(t_data data, int oldfd, int fd, char *s);
int		run_echo(t_data data, int fd, int i, int j);
int		is_builtin(t_data data);
int		get_here_doc(char *delim);
int		find_end(char *arg, int i);
int		ft_strcmp_n(char *s1, char *s2, int len);
int		iter_arg(char *arg, int i, int flag);
int		check_special(char *s);

size_t	sslen(char **ss);

void	freedata(t_data data);
void	freess(char **ss);
void	getexe(t_cmd *cmd);
void	getinredir(t_cmd *cmd);
void	getoutredir(t_cmd *cmd);
void	run_pwd(t_data data);
void	run_env(t_data data);
void	run_exit(t_data data, int i);
void	run_cd(t_cmd *command, char ***envp, int flag);
void	run_export(t_cmd *command, char ***envp, int flag, int check);
void	run_unset(t_cmd *command, char ***envp);
void	exec_b(t_data data, char *s);
void	check_cmd(t_data data, int tmpfd);
void	exec_loop(t_data data, int index, char *i);
void	printss(char **ss);
void	child_process(t_data data, int fd[2]);
void	mini_perror(char *err_str, int err_code, int flag);
void	siginthandler(int sig);
int		exec_fork(t_data data, int i, int pid, int infilepresent);
void	close_exit(int fd[2]);
void	parent_wait(t_data data, int i);
void	ft_freelist(t_list *list);
void	print_export(char **envp);

#endif

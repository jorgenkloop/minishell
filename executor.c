#include "minishell.h"
#include "libft/libft.h"

/*
Identifies and then duplicates any stout and stin redirs
*/
/*
void	setupredirs(t_data data)
{

}
*/

void	printss2(char **ss)
{
	char	**ptr;

	ptr = ss;
	while(*ptr != 0)
	{
		printf("%s ", *ptr);
		ptr++;
	}
	printf("\n");
}


/*
Returns the size of a given list.
Returns 0 if a list is null.
We use ptr to avoid pushing the list forward.
List remains unchanged at the end of the function.
*/
size_t	listsize(t_list *list)
{
	size_t	res;
	t_list *ptr;
	
	res = 1;
	ptr = list;
	if (list == 0)
		return (0);
	while (ptr->next != 0)
	{
		res++;
		ptr = ptr->next;
	}
	return (res);
}

/*
Merges exe->s and args->s found in data->cmd into a single string array.
To be used as second parameter in execve in run_builtin
ft_strdup is not necessary. The strings inside res only need to be read,
not written. Plus it makes memory freeing easier.
*/
char **getexeargs(t_data data)
{
	size_t	len;
	size_t	i;
	char	**res;
	t_list	*ptr;
		
	len = listsize(data.cmd->exe) + listsize(data.cmd->args);
	i = 0;
	res = malloc(sizeof(char *) * (len + 1));
	ptr = data.cmd->args;
	res[len] = 0;
	res[i] = data.cmd->exe->s;
	while (i++, ptr != 0)
	{
		res[i] = ptr->s;
		ptr = ptr->next;
	}
	return (res);
}

/*
prints to stderror (2) error message if execve fails.
mimics the default message on shell as much as possible.
*/
void	builtinerror(char *str1, char *wrongcmd, char *str2)
{
	write(2, str1, ft_strlen(str1));
	write(2, wrongcmd, ft_strlen(wrongcmd));
	write(2, str2, ft_strlen(str2));
}

/*
Runs the builtin commands ie cat, ls, echo, wc via execve
Writes ("bash: <command>: command not found\n") to stderror if fails.
Uses fork() because we don't want minishell to terminate after completing
an execve command. 
Instead we want minishell to continue looping back its readline input
from the main function.
We should use iter_dir() to find the proper PATH dir, but for now I use /bin/
*/
void	run_builtin(t_data data, int res)
{
	//int	fd;
	pid_t	pid;
	char	*joined;
	char	**exeargs;
	
	//fd = 1;
	joined = ft_strjoin("/bin/", data.cmd->exe->s);
	exeargs = getexeargs(data);	
	pid = fork();
	if (!pid)
	{
		//if (fd != 1)
			//dup2(fd, 1);
		res = execve(joined, exeargs, data.envp);
	}
	//if (fd != 1)
		//close (fd);
	waitpid(pid, 0, 0);	
	if (res == -1)
		builtinerror("bash: ", data.cmd->exe->s, ": command not found\n");
	//memory cleanup goes here.
	free(joined);
	free(exeargs);
}

/*
Runs either builtin or 6 of the required self-coded commands
depending on the exe keyword captured.
But for testing we just make everything run_builtin.
*/
void	execute(t_data data)
{
	//setupredirs(data);
	if (!ft_strncmp(data.cmd->exe->s, "echo", 4))
	{
		//run_echo(data);
		run_builtin(data, 0);
	}
	else if (data.cmd->exe->s != 0)
	{
		run_builtin(data, 0);
	}
}

/*
we have two paths: if pipe detected and if pipe not detected.
run execute immediately if no pipe detected(data.cmd->next == 0)
else set up pipe then run execute in a loop.
function length too long but I will optimize later.
*/
t_data	executor(t_data data)
{
	//int	pipe_fd[2];
	//pid_t	pid;
	
	if (data.cmd->next == 0)
	{
		execute(data);
	}
	else
	{
	/*
		pipe(pipe_fd);
		pid = fork();
		while(data.cmd != 0)
		{
			if (pid == 0 && data.cmd->next != 0)
			{
					printf("executing %s\n", data.cmd->exe->s);
					//close(pipe_fd[0]);
					dup2(pipe_fd[1], 1);
					execute(data);
					exit(0);
					//waitpid(pid, 0, 0);
			}
			else if (pid == 0 && data.cmd->next == 0)
			{
				printf("executing %s\n", data.cmd->exe->s);
					//close(pipe_fd[1]);
				dup2(pipe_fd[0], 0);
				execute(data);
				exit(0);
			}
			//printf("Hello!\n");
			printf("done with execution of %s, now we wait\n", data.cmd->exe->s);
			data.cmd = data.cmd->next;	

		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		*/
	}
	return (data);
}

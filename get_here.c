#include "minishell.h"
#include "libft/libft.h"

//reads string from the input and stops when delim is typed
static char	*get_here_string(char *delim, int len)
{
	char	*read;
	char	*ret;
	char	*temp;

	read = NULL;
	ret = NULL;
	temp = NULL;
	while (ft_strncmp(delim, read, len))
	{
		temp = ret;
		ret = ft_strjoin(ret, read);
		free(temp);
		free(read);
		read = readline("> ");
		if (!read)
			break ;
		temp = read;
		read = ft_strjoin(read, "\n");
		free(temp);
	}
	free(read);
	return (ret);
}

//creates a pipe for the readline and writes the input to fd[0]
int	get_here_doc(char *delim)
{
	char	*s;
	int		fd[2];

	if (pipe(fd) < 0)
		return (-1);
	s = get_here_string(delim, ft_strlen(delim));
	write(fd[1], s, ft_strlen(s));
	free(s);
	close(fd[1]);
	return (fd[0]);
}

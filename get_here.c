/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:36:05 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:36:07 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (1)
	{
		if (read != NULL && (int)ft_strlen(read) == (len + 1)
			&& !ft_strncmp(delim, read, len))
			break ;
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

int	ft_strcmp_n(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	if ((int)ft_strlen(s1) != len)
		return (1);
	if (len == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < len - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
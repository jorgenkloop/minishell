/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:32:28 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/03/11 11:51:09 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	find(char *append_line)
{
	int	i;

	i = 0;
	while (append_line[i] && append_line[i] != '\n')
		i++;
	return (i);
}

static char	*newline(char *append_line, int i)
{
	char	*ret;
	int		ctr;

	ctr = 0;
	if (!append_line[ctr])
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (i + 2));
	if (!ret)
		return (NULL);
	while (ctr <= i)
	{
		ret[ctr] = append_line[ctr];
		ctr++;
	}
	ret[ctr] = '\0';
	return (ret);
}

static char	*readline(int fd, char *append_line)
{
	char	*buf;
	int		bytes_read;

	bytes_read = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!ft_memstrchr(append_line, '\n', 0) && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		append_line = ft_gnljoin(append_line, buf);
	}
	free(buf);
	return (append_line);
}

char	*get_next_line(int fd)
{
	static char		*append_line;
	char			*ret;
	int				line;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	append_line = readline(fd, append_line);
	if (!append_line)
		return (NULL);
	line = find(append_line);
	ret = newline(append_line, line);
	if (!append_line[line])
	{
		free(append_line);
		append_line = NULL;
	}
	else
		append_line = ft_memstrchr(append_line, line, 1);
	return (ret);
}

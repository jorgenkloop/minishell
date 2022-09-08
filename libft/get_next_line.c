/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramli <riramli@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:00:00 by riramli           #+#    #+#             */
/*   Updated: 2022/10/01 00:00:00 by riramli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_find_end(char *cache);
static int	gnl_buffer(char **cache, int fd);
static char	*gnl_make_line(char *cache);
static void	gnl_update_cache(char **cache, char *line);

char	*get_next_line(int fd)
{
	static char	*cache[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	while (!gnl_find_end(cache[fd]))
	{
		if (gnl_buffer(&cache[fd], fd) <= 0)
			break ;
	}
	line = gnl_make_line(cache[fd]);
	gnl_update_cache(&cache[fd], line);
	return (line);
}

static void	gnl_update_cache(char **cache, char *line)
{
	char	*temp;
	size_t	strlen_cache;
	size_t	strlen_line;

	if (*cache == 0)
		return ;
	strlen_cache = ft_strlen(*cache);
	strlen_line = ft_strlen(line);
	temp = *cache;
	*cache = ft_substr(*cache, strlen_line, strlen_cache - strlen_line);
	free(temp);
	if (**cache == '\0')
	{
		free(*cache);
		*cache = NULL;
	}
}

static char	*gnl_make_line(char *cache)
{
	char	*line;
	int		end;

	if (cache == 0)
		return (0);
	end = gnl_find_end(cache);
	if (end <= 0)
		line = ft_strdup(cache);
	else
		line = ft_substr(cache, 0, end);
	return (line);
}

static int	gnl_buffer(char **cache, int fd)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == 0)
		return (0);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (*cache)
		{
			temp = *cache;
			*cache = ft_strjoin(*cache, buffer);
			free(temp);
		}
		else if (*cache == 0)
			*cache = ft_strdup(buffer);
	}
	free(buffer);
	return (bytes_read);
}

static int	gnl_find_end(char *cache)
{
	int	i;

	if (cache == 0)
		return (0);
	i = 0;
	while (cache[i])
	{
		if (cache[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}
// /*
// //remember to uncomment before testing with 'make t'
// #include <stdio.h>
// int	main(void)
// {
// 	int fd; 
// 	int read;
// 	char 	*line;
// 	char	*str;

// 	fd = open("text", O_RDONLY);
// 	read = 0;
// 	line = 0;
// 	str = 0;
// 	while (read == 0)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			read = 1;
// 		else
// 			str = ft_strjoin(str, line);
// 	}
// 	printf("%s\n", str);
// 	free(line);
// 	free(str);
// }
// */

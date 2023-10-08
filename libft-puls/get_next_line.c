/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:29:32 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/08 17:04:53 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_make(char *line);
static char	*read_line(char *line, int fd, char *buf);
static void	*free_gnl(char *str);

char	*get_next_line(int fd)
{
	static char	*content = NULL;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = (char *)malloc_ee(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_gnl(content));
	line = read_line(content, fd, buf);
	free (buf);
	if (!line)
		return (NULL);
	content = line_make(line);
	return (line);
}

static char	*read_line(char *line, int fd, char *buf)
{
	size_t	read_bytes;
	char	*line_tmp;

	while (1)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == 0)
			break ;
		buf[read_bytes] = '\0';
		if (!line)
			line = ft_strdup("");
		if (!line)
			return (NULL);
		line_tmp = line;
		line = ft_strjoin(line_tmp, buf);
		free (line_tmp);
		line_tmp = NULL;
		if (!line)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (line);
}

static char	*line_make(char *line)
{
	char	*content;
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	content = ft_strdup(&line[i + 1]);
	if (*content == '\0')
		return (free_gnl(content));
	line[i + 1] = '\0';
	return (content);
}

size_t	ft_strlen(const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

static void	*free_gnl(char *str)
{
	free (str);
	return (NULL);
}

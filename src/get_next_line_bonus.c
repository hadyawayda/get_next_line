/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 04:46:56 by hawayda           #+#    #+#             */
/*   Updated: 2024/08/17 04:47:03 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_to_buffer(int fd, char *buf)
{
	char	*chunk;
	int		read_bytes;

	chunk = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!chunk)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(buf, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, chunk, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(chunk);
			return (NULL);
		}
		chunk[read_bytes] = '\0';
		buf = ft_strjoin(buf, chunk);
		if (!buf)
		{
			free(chunk);
			return (NULL);
		}
	}
	free(chunk);
	return (buf);
}

char	*read_next_line(char *buf)
{
	int		i;
	char	*next_line;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	next_line = malloc(sizeof(char) * (i + 2));
	if (!next_line)
		return (NULL);
	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
	{
		next_line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
	{
		next_line[i] = buf[i];
		i++;
	}
	next_line[i] = '\0';
	return (next_line);
}

char	*update_buffer(char *buf)
{
	char	*new_buf;
	int		i;
	int		j;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	new_buf = malloc(sizeof(char) * (ft_strlen(buf) - i + 1));
	if (!new_buf)
	{
		free(buf);
		return (NULL);
	}
	i++;
	j = 0;
	while (buf[i])
		new_buf[j++] = buf[i++];
	new_buf[j] = '\0';
	free(buf);
	return (new_buf);
}

char	*get_next_line(int fd)
{
	static char	*buf[1024];
	char		*next_line;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (buf[fd])
		{
			free(buf[fd]);
			buf[fd] = NULL;
		}
		return (NULL);
	}
	if (!buf[fd])
		buf[fd] = ft_strdup("");
	buf[fd] = read_to_buffer(fd, buf[fd]);
	if (!buf[fd])
		return (NULL);
	next_line = read_next_line(buf[fd]);
	buf[fd] = update_buffer(buf[fd]);
	return (next_line);
}

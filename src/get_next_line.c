/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 04:28:17 by hawayda           #+#    #+#             */
/*   Updated: 2024/06/23 04:28:24 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_buffer(int fd, char *buf)
{
	char	*chunk;
	int		read_bytes;

	read_bytes = 1;
	chunk = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!chunk)
		return (NULL);
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
	static char	*buf;
	char		*next_line;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (buf)
		{
			free(buf);
			buf = NULL;
		}
		return (NULL);
	}
	if (!buf)
		buf = ft_strdup("");
	buf = read_to_buffer(fd, buf);
	if (!buf)
		return (NULL);
	next_line = read_next_line(buf);
	buf = update_buffer(buf);
	return (next_line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksae-hyu <ksae-hyu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:34:33 by ksae-hyu          #+#    #+#             */
/*   Updated: 2021/10/02 17:00:50 by ksae-hyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*cpy_content(int fd, char *line_content)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(line_content, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		line_content = ft_strjoin(line_content, buffer);
	}
	free(buffer);
	buffer = NULL;
	return (line_content);
}

static char	*extract_from_full_line(char *line_content)
{
	char	*extract_str;
	int		i;

	if (!*line_content)
		return (NULL);
	i = 0;
	while (line_content[i] && line_content[i] != '\n')
		i++;
	extract_str = (char *)malloc(sizeof(char) * (i + 2));
	if (!extract_str)
		return (NULL);
	i = 0;
	while (line_content[i] && line_content[i] != '\n')
	{
		extract_str[i] = line_content[i];
		i++;
	}
	if (line_content[i] == '\n')
	{
		extract_str[i] = line_content[i];
		i++;
	}
	extract_str[i] = '\0';
	return (extract_str);
}

static char	*remove_from_line(char *line_content)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (line_content[i] && line_content[i] != '\n')
		i++;
	if (!line_content[i])
	{
		free(line_content);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(line_content) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (line_content[i])
		str[j++] = line_content[i++];
	str[j] = '\0';
	free(line_content);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line_content;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line_content = cpy_content(fd, line_content);
	if (!line_content)
		return (NULL);
	line = extract_from_full_line(line_content);
	line_content = remove_from_line(line_content);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:48:51 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/10 02:19:04 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_fd(int fd, char *line)
{
	char	*buff;
	ssize_t	counter;

	counter = 1;
	buff = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_strchr(line, '\n') && counter > 0)
	{
		counter = read(fd, buff, BUFFER_SIZE);
		if (counter == -1)
			return (free(buff), NULL);
		buff[counter] = '\0';
		line = ft_strjoin(line, buff);
	}
	free(buff);
	return (line);
}

static char	*c_first_part(char *line)
{
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	return (ft_substr(line, 0, i + 1));
}

static char	*c_remaining_part(char *line)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	str = ft_substr(line + i + 1, 0, ft_strlen(line) - i + 1);
	free(line);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*current;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_fd(fd, line);
	if (!line)
		return (NULL);
	current = c_first_part(line);
	line = c_remaining_part(line);
	return (current);
}

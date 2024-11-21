/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_map_helper3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:40:12 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/21 09:59:02 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checker(char *game, char c, t_data *data)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (game[i])
	{
		if (game[i] == c)
			counter++;
		i++;
	}
	if (counter != 1)
		error(data);
}

void	line_check(char *game, t_data *data, char *trimmed)
{
	int	i;

	i = 0;
	while (game[i])
	{
		if (game[i] != ' ' && game[i] != '\n')
		{
			free(trimmed);
			error(data);
		}
		i++;
	}
}

char	*ft_copy(char *s1, int len)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		res[i] = s1[i];
		i++;
	}
	while (i < len)
	{
		res[i] = ' ';
		i++;
	}
	res[i] = '\0';
	return (res);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_strtrim(char *s1)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = 0;
	if (s1)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ((s1[i] >= 9 && s1[i] <= 13) || s1[i] == 32))
			i++;
		while (s1[j - 1] && ((s1[j - 1] >= 9 && s1[j - 1] <= 13) || s1[j
					- 1] == 32) && j > i)
			j--;
		str = malloc(sizeof(char) * (j - i + 1));
		if (str)
			ft_strlcpy(str, &s1[i], j - i + 1);
	}
	return (str);
}

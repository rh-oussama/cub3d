/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_tools2_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:20:42 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/12 04:37:46 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*get_next_word(char **s, char c)
{
	char		*start;
	const char	*end;
	char		*wd;

	while (**s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	end = *s;
	wd = ft_substr(start, 0, end - start);
	return (wd);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	res = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		res[i] = get_next_word(&s, c);
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	flood_checker(char **map, int i, int j)
{
	if (map[i][j] == 'F' || map[i][j] == '0')
	{
		if (map[i - 1][j] == 'X' || map[i + 1][j] == 'X' || map[i][j - 1] == 'X'
			|| map[i][j + 1] == 'X')
			return (1);
	}
	if (map[i][j] == 'D')
	{
		if (map[i - 1][j] == '1' && map[i + 1][j] == '1' && map[i][j - 1] == '1'
			&& map[i][j + 1] == '1')
			return (1);
	}
	if (map[i][j] == 'D')
	{
		if (map[i - 1][j] == 'X' || map[i + 1][j] == 'X' || map[i][j - 1] == 'X'
			|| map[i][j + 1] == 'X')
			return (1);
	}
	return (0);
}

int	check_path(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (flood_checker(map, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

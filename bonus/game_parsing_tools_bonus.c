/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_tools_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:16 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/17 07:16:47 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(t_data *game)
{
	write(2, "Error\n", 6);
	write(2, "You've made a mistake in the configuration file\n", 48);
	write(2, "Respect the rules mentioned in the subject\n", 43);
	write(2, "Try again\n", 10);
	if (game)
		game_free(game);
	exit(1);
}

int	exit_game(t_data *game)
{
	game_free(game);
	exit(0);
}

int	ft_atoi(char *str, t_data *game)
{
	int	i;
	int	res;
	int	flag;

	res = 0;
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] && str[i] >= '0' && str[i] <= '9' && str[i] != ' '
			&& str[i] != '\n')
		{
			flag = 1;
			res = res * 10 + (str[i] - 48);
		}
		i++;
	}
	if (flag == 0)
		error(game);
	return (res);
}

void	first_and_last_row(t_data *game)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (col < game->width)
	{
		if (game->map[0][col] != '1' && game->map[0][col] != 'X')
			error(game);
		col++;
	}
	row = game->height - 1;
	col = 0;
	while (col < game->width)
	{
		if (game->map[row][col] != '1' && game->map[row][col] != 'X')
			error(game);
		col++;
	}
}

char	*validate_path(char *str, t_data *data)
{
	char	*path;
	char	*tmp;

	tmp = str;
	if (!str)
		error(data);
	if (ft_strncmp(str, "NO", 2) && ft_strncmp(str, "SO", 2) && ft_strncmp(str,
			"EA", 2) && ft_strncmp(str, "WE", 2))
		error(data);
	if (str[2] != ' ')
		error(data);
	str += 3;
	if (!(*str))
		error(data);
	while (*str)
	{
		if (ft_isspace(*str) && *str != '\n')
			error(data);
		str++;
	}
	path = ft_strdup(&(tmp[3]));
	free(tmp);
	return (path);
}

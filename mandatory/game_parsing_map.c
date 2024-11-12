/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:01 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/10 02:36:42 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_cub(char **av)
{
	int	i;

	i = 0;
	while (av[1][i])
		i++;
	if (av[1][i - 1] != 'b' || av[1][i - 2] != 'u' || av[1][i - 3] != 'c'
		|| av[1][i - 4] != '.')
		error("Map name is not valid!");
}

int	is_valid_character(char c)
{
	return (c == '\n' || c == '1' || c == '0' || c == 'S' || c == 'N'
		|| c == 'E' || c == 'W' || c == ' ');
}

void	validate_map_characters(t_data *game)
{
	int	row;
	int	col;
	int	player_count;

	row = 0;
	player_count = 0;
	while (row < game->height)
	{
		col = 0;
		while (col < (int)ft_strlen(game->map[row]))
		{
			if (!is_valid_character(game->map[row][col]))
				error_msg_2("Invalid map character", game);
			if (game->map[row][col] == ' ')
				game->map[row][col] = 'X';
			if (game->map[row][col] == 'S' || game->map[row][col] == 'N'
				|| game->map[row][col] == 'E' || game->map[row][col] == 'W')
				player_count++;
			col++;
		}
		row++;
	}
	if (player_count != 1)
		error_msg_2("You need 1 player", game);
}

void	get_width(t_data *data, int x)
{
	int	lines;

	lines = x;
	while (data->map_checker[lines])
	{
		if ((int)ft_strlen(data->map_checker[lines]) > data->width)
			data->width = (int)ft_strlen(data->map_checker[lines]);
		lines++;
	}
}

void	map_parsing(t_data *game, char **av)
{
	check_cub(av);
	get_map(game, av);
	map_configure(game, 0, 0, NULL);
	validate_map_characters(game);
	is_map_closed(game);
	first_and_last_row(game);
	get_color(game);
	get_textures(game);
	check_map(game);
}

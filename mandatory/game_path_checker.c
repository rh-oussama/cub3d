/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_path_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:24 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/10 02:19:04 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_map(t_data *game)
{
	int	i;

	i = 0;
	game->new_map = malloc((game->height + 1) * sizeof(char *));
	while (game->map[i])
	{
		game->new_map[i] = ft_strdup(game->map[i]);
		i++;
	}
	game->new_map[i] = NULL;
}

void	set_player_position(t_data *game, int row, int col, double angle)
{
	game->p.x = col * TILE_SIZE + TILE_SIZE / 2;
	game->p.y = row * TILE_SIZE + TILE_SIZE / 2;
	game->co_x = col;
	game->co_y = row;
	game->p.angle = angle;
}

void	get_player_position(t_data *game)
{
	int	row;
	int	col;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'W')
				set_player_position(game, row, col, PI_180);
			else if (game->map[row][col] == 'N')
				set_player_position(game, row, col, PI_270);
			else if (game->map[row][col] == 'E')
				set_player_position(game, row, col, 0);
			else if (game->map[row][col] == 'S')
				set_player_position(game, row, col, PI_90);
			col++;
		}
		row++;
	}
}

void	flood(char **str, int x, int y, t_data *game)
{
	if (x < 0 || y < 0 || y >= game->height || x >= (int)ft_strlen(str[y]))
		return ;
	if (str[y][x] == '1' || str[y][x] == 'F' || str[y][x] == 'X')
		return ;
	else
	{
		str[y][x] = 'F';
		flood(str, x + 1, y, game);
		flood(str, x - 1, y, game);
		flood(str, x, y + 1, game);
		flood(str, x, y - 1, game);
	}
}

void	check_map(t_data *game)
{
	get_player_position(game);
	copy_map(game);
	flood(game->new_map, game->co_x, game->co_y, game);
	if (check_path(game->new_map))
		error_msg_2("invalid path in the map", game);
}

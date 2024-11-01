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

void	get_p_pos(t_data *game)
{
	int row;
	int col;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'W' || game->map[row][col] == 'N' || game->map[row][col] == 'E' || game->map[row][col] == 'S')
			{
				game->player_x = col;
				game->player_y = row;
				return ;
			}
			col++;
		}
		col = 0;
		row++;
	}
}

void	flood(char **str, int x, int y, t_data *game)
{
	if (x < 0 || y < 0 || y >= game->height || x >= (int)ft_strlen(str[y]))
		return ;
	if (str[y][x] == '1' || str[y][x] == 'F' || str[y][x] == 'D' || str[y][x] == 'X')
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
			if (map[i][j] == 'F' || map[i][j] == '0')
			{
				if (map[i - 1][j] == 'X' || map[i + 1][j] == 'X' || map[i][j - 1] == 'X' || map[i][j + 1] == 'X')
					return (1);
			}
			if (map[i][j] == 'D')
			{
				if (map[i - 1][j] == '1' && map[i + 1][j] == '1' && map[i][j - 1] == '1' && map[i][j + 1] == '1')
					return (1);
			}
			if (map[i][j] == 'D')
			{
				if (map[i - 1][j] == 'X' || map[i + 1][j] == 'X' || map[i][j - 1] == 'X' || map[i][j + 1] == 'X')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	check_map(t_data *game)
{
	get_p_pos(game);
	copy_map(game);
	flood(game->new_map, game->player_x, game->player_y, game);
	if (check_path(game->new_map))
	{
		//free_map(game->new_map);
		error_msg("invalid path in the map");
	}
}
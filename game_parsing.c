#include "cub3d.h"

int	check_cub(char **av)
{
	int i;

	i = 0;
	while (av[1][i])
		i++;
	if (av[1][i - 1] == 'b' && av[1][i - 2] == 'u' && av[1][i
		- 3] == 'c' && av[1][i - 4] == '.')
		return (0);
	else
	{
		error_msg("Map name is not valid!");
		return (1);
	}
}

void	validate_map_characters(t_data *game)
{
	int row = 0;
	int col;
	int x = 0;
	while (row < game->height)
	{
		col = 0;
		while (col < game->width)
		{
			if (game->map[row][col] != '1' && game->map[row][col] != '0' && game->map[row][col] != 'S' && game->map[row][col] != 'N' && game->map[row][col] != 'E' && game->map[row][col] != 'W')
				error_msg("Invalid map character");
			if (game->map[row][col] == 'S' || game->map[row][col] == 'N' || game->map[row][col] == 'E' || game->map[row][col] == 'W')
				x++;
			col++;
		}
		row++;
	}
	if (x != 1)
		error_msg("You need 1 player");
}

int	is_closed_map(t_data *game)
{
	int i;

	i = 0;
	while (i < game->width)
	{
		if (game->map[0][i] != '1' || game->map[game->height
			- 1][i] != '1')
			error_msg("The map is not closed.");
		i++;
	}
	i = 1;
	while (i < game->height - 1)
	{
		if (game->map[i][0] != '1' || game->map[i][game->width
			- 1] != '1')
			error_msg("The map is not surrounded by walls.");
		i++;
	}
	return (1);
}

void	get_map(t_data *data, char **av)
{
	char *str = NULL;
	int fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_msg("There is no file with that name");
	str = get_next_line(fd);
	if (str == NULL)
		error_msg("The file is empty");
	free(str);
	int w = 1;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		free(str);
		w++;
	}
	fd = open(av[1], O_RDONLY);
	data->map = malloc(((w + 1) * sizeof(char *)));
	w = 0;
	while (1)
	{
		data->map[w] = get_next_line(fd);
		if (data->map[w] == NULL)
			break ;
		w++;
	}
	data->height  = w;
	data->width  = ft_strlen(data->map[0]) - 1;
}

void	map_parsing(t_data *game, char **av)
{
	check_cub(av);
	get_map(game, av);
	validate_map_characters(game);
	is_closed_map(game);
}

#include "cub3d.h"

void	get_color(t_data *game)
{
	int i;
	int c_counter;
	int f_counter;

	i = 0;
	f_counter = 0;
	c_counter = 0;
	int j = 0;
	while (game->floor_parse[i])
	{
		while (game->floor_parse[i][j])
		{
			if (!ft_is_num(game->floor_parse[i][j]) && game->floor_parse[i][j] != ',' && game->floor_parse[i][j] != ' ' && game->floor_parse[i][j] != '\n')
				error_msg("Invalid color");
			j++;
		}
		f_counter++;
		i++;
	}
	i = 0;
	j = 0;
	while (game->ceiling_parse[i])
	{
		while (game->ceiling_parse[i][j])
		{
			if (!ft_is_num(game->ceiling_parse[i][j]) && game->ceiling_parse[i][j] != ',' && game->ceiling_parse[i][j] != ' ' && game->ceiling_parse[i][j] != '\n')
				error_msg("Invalid color");
			j++;
		}
		c_counter++;
		i++;
	}
	if (f_counter != 1 || c_counter != 1)
		error_msg("Invalid color");

	f_counter = 0;
	c_counter = 0;
	i = 0;
	while (game->floor_parse[0][i])
	{
		if (game->floor_parse[0][i] == ',')
			f_counter++;
		i++;
	}
	i = 0;
	while (game->ceiling_parse[0][i])
	{
		if (game->ceiling_parse[0][i] == ',')
			c_counter++;
		i++;
	}
	if (f_counter != 2 || c_counter != 2)
		error_msg("Invalid color");

	game->floor_parse = ft_split(game->floor_parse[0], ',');
	game->r = ft_atoi(game->floor_parse[0]);
	game->g = ft_atoi(game->floor_parse[1]);
	game->b = ft_atoi(game->floor_parse[2]);
	if (game->r < 0 || game->r > 255 || game->g < 0 || game->g > 255 || game->b < 0 || game->b > 255)
		error_msg("Invalid color range");
	game->floor_color = (game->r << 16 | game->g << 8 | game->b);

	game->ceiling_parse = ft_split(game->ceiling_parse[0], ',');
	game->r = ft_atoi(game->ceiling_parse[0]);
	game->g = ft_atoi(game->ceiling_parse[1]);
	game->b = ft_atoi(game->ceiling_parse[2]);
	if (game->r < 0 || game->r > 255 || game->g < 0 || game->g > 255 || game->b < 0 || game->b > 255)
		error_msg("Invalid color range");
	game->ceiling_color = (game->r << 16 | game->g << 8 | game->b);
}
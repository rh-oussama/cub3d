#include "cub3d.h"

void validate_color_format(char **color_str)
{
	int i;
	int commas;

	i = 0;
	commas = 0;
	if (!color_str || !color_str[0])
		error_msg("Invalid color (color not provided)");

	while (color_str[0][i])
	{
		if (!ft_is_num(color_str[0][i]) && color_str[0][i] != ',' &&
			color_str[0][i] != ' ' && color_str[0][i] != '\n')
			error_msg("Invalid color");
		if (color_str[0][i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		error_msg("Invalid color (more than one comma)");
}

void get_color(t_data *game)
{
	int r;
	int g;
	int b;

	validate_color_format(game->floor_parse);
	validate_color_format(game->ceiling_parse);
	game->floor_parse = ft_split(game->floor_parse[0], ',');
	r = ft_atoi(game->floor_parse[0]);
	g = ft_atoi(game->floor_parse[1]);
	b = ft_atoi(game->floor_parse[2]);
	if (r < 0 || r > 255 || g < 0 ||
		g > 255 || b < 0 || b > 255)
		error_msg("Invalid color range");
	game->floor_color = (r << 16 | g << 8 | b);

	game->ceiling_parse = ft_split(game->ceiling_parse[0], ',');
	r = ft_atoi(game->ceiling_parse[0]);
	g = ft_atoi(game->ceiling_parse[1]);
	b = ft_atoi(game->ceiling_parse[2]);
	if (r < 0 || r > 255 || g < 0 ||
		g > 255 || b < 0 || b > 255)
		error_msg("Invalid color range");
	game->ceiling_color = (r << 16 | g << 8 | b);
}

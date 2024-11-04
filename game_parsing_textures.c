#include "cub3d.h"

void	validate_color_format(char **color_str)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	if (!color_str || !color_str[0])
		error_msg("Invalid color (color not provided)");
	while (color_str[0][i])
	{
		if (!ft_is_num(color_str[0][i]) && color_str[0][i] != ','
			&& color_str[0][i] != ' ' && color_str[0][i] != '\n')
			error_msg("Invalid color");
		if (color_str[0][i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		error_msg("Invalid color (more than one comma)");
}

void	get_color(t_data *game)
{
	int	r;
	int	g;
	int	b;

	validate_color_format(game->floor_parse);
	validate_color_format(game->ceiling_parse);
	game->floor_parse = ft_split(game->floor_parse[0], ',');
	r = ft_atoi(game->floor_parse[0]);
	g = ft_atoi(game->floor_parse[1]);
	b = ft_atoi(game->floor_parse[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_msg("Invalid color range");
	game->floor_color = (r << 16 | g << 8 | b);
	game->ceiling_parse = ft_split(game->ceiling_parse[0], ',');
	r = ft_atoi(game->ceiling_parse[0]);
	g = ft_atoi(game->ceiling_parse[1]);
	b = ft_atoi(game->ceiling_parse[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_msg("Invalid color range");
	game->ceiling_color = (r << 16 | g << 8 | b);
}

void	textures_check(t_data *game)
{
	t_texture	*t;

	t = game->textures;
	t[0].img = mlx_xpm_file_to_image(game->mlx_ptr, game->no_texture,
			&t[0].width, &t[0].height);
	if (!t[0].img)
		error_msg("No texture found");
	t[0].data = mlx_get_data_addr(t[0].img, &t[0].bpp, &t[0].size_line,
			&t[0].endian);
	t[1].img = mlx_xpm_file_to_image(game->mlx_ptr, game->ea_texture,
			&t[1].width, &t[1].height);
	if (!t[1].img)
		error_msg("No texture found");
	t[1].data = mlx_get_data_addr(t[1].img, &t[1].bpp, &t[1].size_line,
			&t[1].endian);
	t[2].img = mlx_xpm_file_to_image(game->mlx_ptr, game->so_texture,
			&t[2].width, &t[2].height);
	if (!t[2].img)
		error_msg("No texture found");
	t[2].data = mlx_get_data_addr(t[2].img, &t[2].bpp, &t[2].size_line,
			&t[2].endian);
	t[3].img = mlx_xpm_file_to_image(game->mlx_ptr, game->we_texture,
			&t[3].width, &t[3].height);
	if (!t[3].img)
		error_msg("No texture found");
	t[3].data = mlx_get_data_addr(t[3].img, &t[3].bpp, &t[3].size_line,
			&t[3].endian);
}

char	*validate_path(char *str)
{
	char	*path;
	char	*tmp;

	tmp = str;
	if (!str)
		error_msg("Invalid configuration (EMPTY)");
	if (ft_strncmp(str, "NO", 2) && ft_strncmp(str, "SO", 2) && ft_strncmp(str,
			"EA", 2) && ft_strncmp(str, "WE", 2))
		error_msg("Invalid configuration (NO | EA | SO | WE)");
	if (str[2] != ' ')
		error_msg("Invalid configuration (NO SPACE BETWEEN PATH AND DIRECTION)");
	str += 3;
	if (!(*str))
		error_msg("Invalid configuration (EMPTY PATH)");
	while (*str)
	{
		if (ft_isspace(*str) && *str != '\n')
			error_msg("Invalid configuration (FOUND SPACE IN PATH)");
		str++;
	}
	// if alway new line a the end of str
	*(str - 1) = '\0';
	///////////////////////////
	path = ft_strdup(&(tmp[3]));
	free(tmp);
	return (path);
}

void	get_textures(t_data *game)
{
	game->no_texture = validate_path(game->no_texture);
	game->so_texture = validate_path(game->so_texture);
	game->we_texture = validate_path(game->we_texture);
	game->ea_texture = validate_path(game->ea_texture);
}
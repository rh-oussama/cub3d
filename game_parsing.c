#include "cub3d.h"

void	error_msg(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(1);
}

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
	char	*start;
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

void	copy_map(t_data *game)
{
	int	i;

	i = 0;
	game->new_map = NULL;
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
			if (map[i][j] == 'F')
			{
				if (map[i - 1][j] == 'X' || map[i + 1][j] == 'X' || map[i][j - 1] == 'X' || map[i][j + 1] == 'X')
					return (1);
			}
			if (map[i][j] == 'D')
			{
				if (map[i - 1][j] == '1' && map[i + 1][j] == '1' && map[i][j - 1] == '1' && map[i][j + 1] == '1')
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
		error_msg("invalid path in the map");
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
		while (col < (int)ft_strlen(game->map[row]))
		{
			if (game->map[row][col] == ' ')
				game->map[row][col] = 'X';
			if (!game->map[row][col] && game->map[row][col] != '1' && game->map[row][col] != '0' && game->map[row][col] != 'S' && game->map[row][col] != 'N' && game->map[row][col] != 'E' && game->map[row][col] != 'W' && game->map[row][col] != 'X' && game->map[row][col] != 'D')
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

void	get_map(t_data *data, char **av)
{
	char *str = NULL;
	data->map_checker = NULL;
	int fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_msg("There is no file with that name");
	str = get_next_line(fd);
	if (str == NULL)
		error_msg("The file is empty");
	free(str);
	int w = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		free(str);
		w++;
	}
	close(fd);
	fd = open(av[1], O_RDONLY);
	data->map_checker = malloc(((w + 2) * sizeof(char *)));
	w = 0;
	data->map_checker[w] = get_next_line(fd);
	while (data->map_checker[w])
	{
		w++;
		data->map_checker[w] = get_next_line(fd);
	}
	data->map_checker[w] = NULL;
	close(fd);
}


char	*ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
		++i;
	}
	return (0);
}

void	map_configuere(t_data *data)
{
	int x = 0;
	int i = 0;
	int lines = 0;
	int counter = 0;
	data->map = NULL;
	while (data->map_checker[x])
	{
		if (ft_strstr(data->map_checker[x], "NO"))
			data->no_texture = ft_split(data->map_checker[x], ' ')[1];
		else if (ft_strstr(data->map_checker[x], "SO"))
			data->so_texture = ft_split(data->map_checker[x], ' ')[1];
		else if (ft_strstr(data->map_checker[x], "WE"))
			data->we_texture = ft_split(data->map_checker[x], ' ')[1];
		else if (ft_strstr(data->map_checker[x], "EA"))
			data->ea_texture = ft_split(data->map_checker[x], ' ')[1];
		else if (ft_strstr(data->map_checker[x], "F"))
			data->floor = ft_split(data->map_checker[x], ' ')[1];
		else if (ft_strstr(data->map_checker[x], "C"))
			data->ceiling = ft_split(data->map_checker[x], ' ')[1];
		else if (ft_strchr(data->map_checker[x], '1'))
		{
			if (data->no_texture == NULL || data->so_texture == NULL || data->we_texture == NULL || data->ea_texture == NULL || data->floor == NULL || data->ceiling == NULL)
				error_msg("Missing configuration or order is wrong");
			lines = x;
			while (data->map_checker[lines])
			{
				counter++;
				lines++;
			}
			data->map = malloc((counter + 1) * sizeof(char *));
			while (data->map_checker[x])
			{
				data->map[i] = ft_strdup(data->map_checker[x]);
				i++;
				x++;
			}
			data->map[i] = NULL;
			break ;
		}
		x++;
	}
	data->height  = i;
	i = 0;
	int widht = 0;
	while(data->map[i])
	{
		if (data->map[i + 1] == NULL)
			break ;
		if (ft_strlen(data->map[i]) > ft_strlen(data->map[i + 1]))
		{
			if (widht < (int)ft_strlen(data->map[i]))
				widht = (int)ft_strlen(data->map[i]);
		}
		i++;
	}
	data->widht = widht;
}

int	ft_isdigit(int i)
{
	return ('0' <= i && i <= '9');
}


void	is_map_closed(t_data *game)
{
	int row = 0;
	int col = 0;
	while (row < game->height)
	{
		col = 0;
		while (col < (int)ft_strlen(game->map[row]))
		{
			if (ft_isdigit((int)game->map[row][col]))
			{
				if (game->map[row][col] == '1')
					break ;
				else
					error_msg("Map is not closed");
			}
			col++;
		}
		col = (int)ft_strlen(game->map[row]) - 1;
		while (col >= 0)
		{
			if (ft_isdigit((int)game->map[row][col]))
			{
				if (game->map[row][col] == '1')
					break ;
				else
					error_msg("Map is not closed");
			}
			col--;
		}
		row++;
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	res = 0;
	neg = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * neg);
}

void	get_color(t_data *game)
{
	char **f;
	char **c;
	int i;
	int c_counter;
	int f_counter;
	int r;
	int g;
	int b;

	i = 0;
	f_counter = 0;
	c_counter = 0;
	f = NULL;
	c = NULL;
	while (game->floor[i])
	{
		if (game->floor[i] == ',')
			f_counter++;
		i++;
	}
	i = 0;
	while (game->ceiling[i])
	{
		if (game->ceiling[i] == ',')
			c_counter++;
		i++;
	}
	if (f_counter != 2 || c_counter != 2)
		error_msg("Invalid color");
	f = ft_split(game->floor, ',');
	c = ft_split(game->ceiling, ',');

	if (!f || !f[0] || !f[1] || !f[2] || !c || !c[0] || !c[1] || !c[2])
		error_msg("Invalid color format");

	r = ft_atoi(f[0]);
	g = ft_atoi(f[1]);;
	b = ft_atoi(f[2]);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_msg("Invalid color range");
	game->floor_color = (r << 16 | g << 8 | b);
	r = ft_atoi(c[0]);
	g = ft_atoi(c[1]);
	b = ft_atoi(c[2]);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_msg("Invalid color range");
	game->ceiling_color = (r << 16 | g << 8 | b);
}

void	textures_check(t_data *game)
{
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx_ptr, "textures/wall.xpm", &game->textures[0].width, &game->textures[0].height);
	if (game->textures[0].img == NULL)
		error_msg("No texture found");
	game->textures[0].data = mlx_get_data_addr(game->textures[0].img, &game->textures[0].bpp, &game->textures[0].size_line, &game->textures[0].endian);
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx_ptr, "textures/wall.xpm", &game->textures[1].width, &game->textures[1].height);
	if (game->textures[1].img == NULL)
		error_msg("No texture found");
	game->textures[1].data = mlx_get_data_addr(game->textures[1].img, &game->textures[1].bpp, &game->textures[1].size_line, &game->textures[1].endian);
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx_ptr, "textures/wall.xpm", &game->textures[2].width, &game->textures[2].height);
	if (game->textures[2].img == NULL)
		error_msg("No texture found");
	game->textures[2].data = mlx_get_data_addr(game->textures[2].img, &game->textures[2].bpp, &game->textures[2].size_line, &game->textures[2].endian);
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx_ptr, "textures/wall.xpm", &game->textures[3].width, &game->textures[3].height);
	if (game->textures[3].img == NULL)
		error_msg("No texture found");
	game->textures[3].data = mlx_get_data_addr(game->textures[3].img, &game->textures[3].bpp, &game->textures[3].size_line, &game->textures[3].endian);
}

void	map_parsing(t_data *game, char **av)
{
	check_cub(av);
	get_map(game, av);
	map_configuere(game);
	validate_map_characters(game);
	is_map_closed(game);
	check_map(game);
	get_color(game);
}

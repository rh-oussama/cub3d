#include "cub3d.h"

void	check_cub(char **av)
{
	int i;

	i = 0;
	while (av[1][i])
		i++;
	if (av[1][i - 1] != 'b' && av[1][i - 2] != 'u' && av[1][i
		- 3] == 'c' && av[1][i - 4] != '.')
		error_msg("Map name is not valid!");
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
			if (game->map[row][col] != '\n' && game->map[row][col] != '1' && game->map[row][col] != '0' && game->map[row][col] != 'S' && game->map[row][col] != 'N' && game->map[row][col] != 'E' && game->map[row][col] != 'W' && game->map[row][col] != ' ' && game->map[row][col] != 'D')
			{
				printf("--%c--\n", game->map[row][col]);
				error_msg("Invalid map character");
			}
			if (game->map[row][col] == ' ')
				game->map[row][col] = 'X';
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
	close(fd);
	fd = open(av[1], O_RDONLY);
	data->map_checker = malloc(((w + 1) * sizeof(char *)));
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


void	checker(char *game, char c)
{
	int i = 0;
	int counter = 0;
	while (game[i])
	{
		if (game[i] == c)
			counter++;
		i++;
	}
	if (counter != 1)
		error_msg("Invalid configuration");
}

void	line_check(char *game)
{
	int i = 0;
	while (game[i])
	{
		if (game[i] != ' ' && game[i] != '1' && game[i] != '0' && game[i] != 'S' && game[i] != 'N' && game[i] != 'E' && game[i] != 'W' && game[i] != 'D' && game[i] != '\n')
			error_msg("Error");
		i++;
	}
}

char	*ft_copy(char *s1, int len)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		res[i] = s1[i];
		i++;
	}
	while (i < len)
	{
		res[i] = ' ';
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	map_configure(t_data *data)
{
	int x = 0;
	int i = 0;
	int lines = 0;
	int counter = 0;
	int flag = 0;
	int size = 0;
	while (data->map_checker[x])
	{
		if (flag > 6)
			error_msg("Invalid configuration");
		if (ft_strstr(data->map_checker[x], "NO"))
		{
			data->no_texture = ft_strdup(data->map_checker[x]);
			flag++;
		}
		else if (ft_strstr(data->map_checker[x], "SO"))
		{
			data->so_texture = ft_strdup(data->map_checker[x]);
			flag++;
		}
		else if (ft_strstr(data->map_checker[x], "WE"))
		{
			data->we_texture = ft_strdup(data->map_checker[x]);
			flag++;
		}
		else if (ft_strstr(data->map_checker[x], "EA"))
		{
			data->ea_texture = ft_strdup(data->map_checker[x]);
			flag++;
		}
		else if (ft_strchr(data->map_checker[x], 'F') && ft_strchr(data->map_checker[x], ','))
		{
			checker(data->map_checker[x], 'F');
			data->floor_parse = ft_split(data->map_checker[x], 'F');
			flag++;
		}
		else if (ft_strchr(data->map_checker[x], 'C') && ft_strchr(data->map_checker[x], ','))
		{
			checker(data->map_checker[x], 'C');
			data->ceiling_parse = ft_split(data->map_checker[x], 'C');
			flag++;
		}
		else if (ft_strchr(data->map_checker[x], '1'))
		{
			if (!data->no_texture || !data->so_texture || !data->we_texture || !data->ea_texture || !data->floor_parse || !data->ceiling_parse)
				error_msg("Missing configuration or order is wrong");
			lines = x;
			while (data->map_checker[lines])
			{
				if (!ft_strchr(data->map_checker[lines], '1'))
					size++;
				else
					size = 0;
				counter++;
				lines++;
			}
			int width = 0;
			int row = x;
			while(data->map_checker[row])
			{
				if ((int)ft_strlen(data->map_checker[row]) > width)
					width = (int)ft_strlen(data->map_checker[row]);
				row++;
			}
			data->width = width;
			data->map = malloc(((counter - size) + 1) * sizeof(char *));
			while (data->map_checker[x])
			{
				data->map[i] = ft_copy(data->map_checker[x], data->width);
				i++;
				x++;
			}
			data->map[i] = NULL;
			data->height  = i;
			i = 0;
			return ;
		}
		else
			line_check(data->map_checker[x]);
		x++;
	}
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
			if (ft_isalpha_num(game->map[row][col]) && game->map[row][col] != 'X')
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
			if (ft_isalpha_num(game->map[row][col]) && game->map[row][col] != 'X')
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

void	map_parsing(t_data *game, char **av)
{
	check_cub(av);
	get_map(game, av);
	map_configure(game);
	validate_map_characters(game);
	is_map_closed(game);
	get_color(game);
	get_textures(game);
	check_map(game);
}

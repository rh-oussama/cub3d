/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_map_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:11:12 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/14 15:20:51 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines(char **av)
{
	char	*str;
	int		fd;
	int		w;

	str = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error(NULL);
	str = get_next_line(fd);
	if (str == NULL)
		error(NULL);
	free(str);
	w = 1;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		free(str);
		w++;
	}
	close(fd);
	return (w);
}

void	get_map(t_data *data, char **av)
{
	int	fd;
	int	w;

	fd = open(av[1], O_RDONLY);
	w = count_lines(av);
	data->map_checker = malloc(((w + 1) * sizeof(char *)));
	w = 0;
	data->map_checker[w] = get_next_line(fd);
	while (data->map_checker[w])
	{
		w++;
		data->map_checker[w] = get_next_line(fd);
	}
	close(fd);
}

void	check_row_left_to_right(t_data *game, int row)
{
	int	col;

	col = 0;
	while (col < (int)ft_strlen(game->map[row]))
	{
		if (ft_isalpha_num(game->map[row][col]) && game->map[row][col] != 'X')
		{
			if (game->map[row][col] == '1')
				break ;
			else
				error(game);
		}
		col++;
	}
}

void	check_row_right_to_left(t_data *game, int row)
{
	int	col;

	col = (int)ft_strlen(game->map[row]) - 1;
	while (col >= 0)
	{
		if (ft_isalpha_num(game->map[row][col]) && game->map[row][col] != 'X')
		{
			if (game->map[row][col] == '1')
				break ;
			else
				error(game);
		}
		col--;
	}
}

void	is_map_closed(t_data *game)
{
	int	row;

	row = 0;
	while (row < game->height)
	{
		check_row_left_to_right(game, row);
		check_row_right_to_left(game, row);
		row++;
	}
}

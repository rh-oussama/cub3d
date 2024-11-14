/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:16 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/14 15:18:55 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error(t_data *game)
{
	write(2, "Error\n", 6);
	if (game)
		game_free(game);
	exit(1);
	return 1;
}

int	exit_game(t_data *game)
{
	game_free(game);
	exit(0);
}

int	ft_atoi(char *str, t_data *game)
{
	int	i;
	int	res;
	int	flag;

	res = 0;
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] && str[i] >= '0' && str[i] <= '9' && str[i] != ' '
			&& str[i] != '\n')
		{
			flag = 1;
			res = res * 10 + (str[i] - 48);
		}
		i++;
	}
	if (flag == 0)
		error(game);
	return (res);
}

void	first_and_last_row(t_data *game)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (col < game->width)
	{
		if (game->map[0][col] != '1' && game->map[0][col] != 'X')
			error(game);
		col++;
	}
	row = game->height - 1;
	col = 0;
	while (col < game->width)
	{
		if (game->map[row][col] != '1' && game->map[row][col] != 'X')
			error(game);
		col++;
	}
}

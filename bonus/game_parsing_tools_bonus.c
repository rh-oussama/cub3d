/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_tools_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:16 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/11 03:44:29 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

int	exit_game(t_data *game)
{
	free_map(game);
	free_new_map(game);
	free_map_checker(game);
	free_door(game);
	free_ceiling(game);
	free_floor(game);
	free_images(game);
	free(game->no_texture);
	free(game->so_texture);
	free(game->we_texture);
	free(game->ea_texture);
	free(game->floor);
	free(game->ceiling);
	mlx_destroy_window(game->mlx_ptr, game->mlx_win);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	exit(0);
}

void	error_msg_2(char *str, t_data *game)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free_floor(game);
	free_ceiling(game);
	free_new_map(game);
	free_map_checker(game);
	free_map(game);
	if (game->no_texture)
		free(game->no_texture);
	if (game->so_texture)
		free(game->so_texture);
	if (game->we_texture)
		free(game->we_texture);
	if (game->ea_texture)
		free(game->ea_texture);
	if (game->floor)
		free(game->floor);
	if (game->ceiling)
		free(game->ceiling);
	exit(1);
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
		error_msg_2("Invalid color", game);
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
			error_msg_2("Map not closed :(", game);
		col++;
	}
	row = game->height - 1;
	col = 0;
	while (col < game->width)
	{
		if (game->map[row][col] != '1' && game->map[row][col] != 'X')
			error_msg_2("Map not closed :(", game);
		col++;
	}
}
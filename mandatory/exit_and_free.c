/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 02:01:06 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/09 22:19:08 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_data *game)
{
	int	i;

	i = 0;
	while (game->map[i] != NULL)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	free_map_checker(t_data *game)
{
	int	i;

	i = 0;
	while (game->map_checker[i] != NULL)
	{
		free(game->map_checker[i]);
		i++;
	}
	free(game->map_checker);
}

void	free_new_map(t_data *game)
{
	int	i;

	i = 0;
	while (game->new_map[i] != NULL)
	{
		free(game->new_map[i]);
		i++;
	}
	free(game->new_map);
}

void	free_images(t_data *game)
{
	int	i;

	i = 0;
	while (i < 4)
		mlx_destroy_image(game->mlx_ptr, game->textures[i++].img);
	mlx_destroy_image(game->mlx_ptr, game->img_2d.img);
	mlx_destroy_image(game->mlx_ptr, game->img_3d.img);
}

int	exit_game(t_data *game)
{
	free_map(game);
	free_new_map(game);
	free_map_checker(game);
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
	exit(1);
}

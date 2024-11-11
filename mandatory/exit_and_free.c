/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 02:01:06 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/10 17:15:31 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_data *game)
{
	int	i;

	i = 0;
	if (!game->map)
		return ;
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
	if (!game->map_checker)
		return ;
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
	if (!game->new_map)
		return ;
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
	if (game->img_2d.img)
		mlx_destroy_image(game->mlx_ptr, game->img_2d.img);
	if (game->img_3d.img)
		mlx_destroy_image(game->mlx_ptr, game->img_3d.img);
}

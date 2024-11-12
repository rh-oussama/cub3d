/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:17:11 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/10 17:16:17 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_ceiling(t_data *game)
{
	int	i;

	i = 0;
	if (!game->ceiling_parse)
		return ;
	while (game->ceiling_parse[i] != NULL)
	{
		free(game->ceiling_parse[i]);
		i++;
	}
	free(game->ceiling_parse);
}

void	free_floor(t_data *game)
{
	int	i;

	i = 0;
	if (!game->floor_parse)
		return ;
	while (game->floor_parse[i] != NULL)
	{
		free(game->floor_parse[i]);
		i++;
	}
	free(game->floor_parse);
}

int	exit_free(t_data *game)
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

void	error_msg(char *str, t_data *game)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit_free(game);
}

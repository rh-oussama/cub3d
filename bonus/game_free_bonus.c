/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_free_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:03:57 by orhaddao          #+#    #+#             */
/*   Updated: 2024/11/18 10:52:04 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_textures(t_data *game, t_texture *text)
{
	int	i;

	i = 0;
	while (text[i].bpp != -13)
	{
		if (text[i].img)
			mlx_destroy_image(game->mlx_ptr, text[i].img);
		i++;
	}
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	destroy_all_image(t_data *data)
{
	destroy_textures(data, data->textures);
	destroy_textures(data, data->first);
	destroy_textures(data, data->second);
	destroy_textures(data, data->third);
	destroy_textures(data, data->fourth);
	destroy_textures(data, data->loading_bar);
	if (data->img_2d.img)
		mlx_destroy_image(data->mlx_ptr, data->img_2d.img);
	if (data->img_3d.img)
		mlx_destroy_image(data->mlx_ptr, data->img_3d.img);
}

void	game_free(t_data *data)
{
	free(data->floor);
	free(data->ceiling);
	free(data->no_texture);
	free(data->so_texture);
	free(data->we_texture);
	free(data->ea_texture);
	free(data->door_tex);
	free(data->ceiling_tex);
	free_2d_array(data->floor_parse);
	free_2d_array(data->ceiling_parse);
	free_2d_array(data->map);
	free_2d_array(data->map_checker);
	free_2d_array(data->new_map);
	free_2d_array(data->door);
	destroy_all_image(data);
	if (data->mlx_ptr && data->mlx_win)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}

int	separate_dist(t_data *data)
{
	int		xy[3];
	char	type;
	int		i;

	i = 0;
	xy[2] = TILE_SIZE;
	while (xy[2] > 0)
	{
		xy[0] = floor((data->p.x + cos(data->p.angle) * xy[2]) / TILE_SIZE);
		xy[1] = floor((data->p.y + sin(data->p.angle) * xy[2]) / TILE_SIZE);
		type = data->door[(int)xy[1]][(int)xy[0]];
		if (type == '0' || type == 'O')
			i++;
		xy[2]--;
	}
	return (i);
}

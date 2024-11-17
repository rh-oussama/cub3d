/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:45 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/17 07:05:19 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_render(t_data *data)
{
	double	old_x;
	double	old_y;
	double	old_angle;

	old_x = data->p.x;
	old_y = data->p.y;
	old_angle = data->p.angle;
	update_player_rotation(data);
	update_player_position(data);
	if (!(old_x == data->p.x && old_y == data->p.y
			&& old_angle == data->p.angle))
		ray_draw(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img_3d.img, 0,
		0);
	return (0);
}

void	init_image(t_data *data)
{
	textures_check(data);
	data->img_2d.width = (data->width * TILE_SIZE);
	data->img_2d.height = (data->height * TILE_SIZE);
	data->img_2d.img = mlx_new_image(data->mlx_ptr, data->img_2d.width,
			data->img_2d.height);
	if (!data->img_2d.img)
		error(data);
	data->img_2d.img_data = mlx_get_data_addr(data->img_2d.img,
			&data->img_2d.bits_per_pixel, &data->img_2d.size_line,
			&data->img_2d.endian);
	data->img_3d.img = mlx_new_image(data->mlx_ptr, data->img_3d.width,
			data->img_3d.height);
	if (!data->img_3d.img)
		error(data);
	data->img_3d.img_data = mlx_get_data_addr(data->img_3d.img,
			&data->img_3d.bits_per_pixel, &data->img_3d.size_line,
			&data->img_3d.endian);
	ray_draw(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		error(NULL);
	game_init(&data);
	map_parsing(&data, av);
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3d");
	init_image(&data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_pressed, &data);
	mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, key_released, &data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, exit_game,
		&data);
	mlx_loop_hook(data.mlx_ptr, game_render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

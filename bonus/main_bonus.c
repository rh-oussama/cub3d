/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:45 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/15 03:52:01 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_render(t_data *data)
{
	update_player_rotation(data);
	update_player_position(data);
	ray_draw(data);
	draw_mini_map(data, 0, 0);
	if (data->key.key_j)
	{
		if ((sprite(data, data->second, 101) + 1) == 101)
			data->key.key_j = 0;
	}
	else if (data->key.key_sp)
	{
		sprite(data, data->third, 14);
		if (data->key.key_w)
			move_player(data, data->p.angle);
	}
	else if (data->key.key_w || data->key.key_a)
		sprite(data, data->fourth, 122);
	else
		sprite(data, data->first, 58);
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
	data->door = new_array(data->map);
	if (!data->door)
		error(data);
	ground_draw(data);
	ray_draw(data);
	draw_mini_map(data, 0, 0);
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	int	delta_x;

	(void)y;
	delta_x = x - (WINDOW_WIDTH / 2);
	if (delta_x != 0 && !(data->key.key_q % 2))
	{
		mlx_mouse_hide(data->mlx_ptr, data->mlx_win);
		data->p.angle += delta_x * MOUSE_SENSITIVITY;
		data->p.angle = normalize_angle(data->p.angle);
		mlx_mouse_move(data->mlx_ptr, data->mlx_win, WINDOW_WIDTH / 2,
			WINDOW_HEIGHT / 2);
	}
	else if (data->key.key_q % 2)
		mlx_mouse_show(data->mlx_ptr, data->mlx_win);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		error(NULL);
	game_init(&data);
	map_parsing(&data, av);
	get_player_position(&data);
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3d");
	init_image(&data);
	game_render(&data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_pressed, &data);
	mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, key_released, &data);
	mlx_hook(data.mlx_win, MotionNotify, PointerMotionMask, handle_mouse_move,
		&data);
	mlx_hook(data.mlx_win, DestroyNotify, StructureNotifyMask, exit_game,
		&data);
	mlx_loop_hook(data.mlx_ptr, game_render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:45 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/12 20:14:49 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_render(t_data *data)
{
	update_player_rotation(data);
	update_player_position(data);
	ray_draw(data);
	draw_mini_map(data, 0, 0);
	if (sprite(data) == 101)
		data->key.key_k = 0;		
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img_3d.img, 0,
		0);
	return (0);
}

void	game_init(t_data *data)
{
	data->img_3d.width = WINDOW_WIDTH;
	data->img_3d.height = WINDOW_HEIGHT;
	data->p.r = 2;
	data->key.key_a = 0;
	data->key.key_s = 0;
	data->key.key_d = 0;
	data->key.key_w = 0;
	data->key.key_k = 0;
	data->key.key_left = 0;
	data->key.key_right = 0;
	data->width = 0;
	data->map_checker = NULL;
	data->map = NULL;
	data->new_map = NULL;
	data->floor_parse = NULL;
	data->ceiling_parse = NULL;
	data->floor = NULL;
	data->ceiling = NULL;
	data->no_texture = NULL;
	data->so_texture = NULL;
	data->we_texture = NULL;
	data->ea_texture = NULL;
	data->door = NULL;
}

void	init_image(t_data *data)
{
	textures_check(data);
	data->img_2d.width = (data->width * TILE_SIZE);
	data->img_2d.height = (data->height * TILE_SIZE);
	data->img_2d.img = mlx_new_image(data->mlx_ptr, data->img_2d.width,
			data->img_2d.height);
	if (!data->img_2d.img)
		error_msg("Error: NO enough memmory 2d", data);
	data->img_2d.img_data = mlx_get_data_addr(data->img_2d.img,
			&data->img_2d.bits_per_pixel, &data->img_2d.size_line,
			&data->img_2d.endian);
	data->img_3d.img = mlx_new_image(data->mlx_ptr, data->img_3d.width,
			data->img_3d.height);
	if (!data->img_3d.img)
		error_msg("Error: NO enough memmory 3d", data);
	data->img_3d.img_data = mlx_get_data_addr(data->img_3d.img,
			&data->img_3d.bits_per_pixel, &data->img_3d.size_line,
			&data->img_3d.endian);
	data->door = new_array(data->map);
	if (!data->door)
		error_msg("No enough memory", data);
	ground_draw(data);
	ray_draw(data);
	draw_mini_map(data, 0, 0);
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	int	delta_x;

	(void)y;
	delta_x = x - (WINDOW_WIDTH / 2);
	if (delta_x != 0)
	{
		data->p.angle += delta_x * MOUSE_SENSITIVITY;
		data->p.angle = normalize_angle(data->p.angle);
		mlx_mouse_move(data->mlx_ptr, data->mlx_win, WINDOW_WIDTH / 2,
			WINDOW_HEIGHT / 2);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		error("No map !");
	game_init(&data);
	map_parsing(&data, av);
	get_player_position(&data);
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3d");
	mlx_mouse_hide(data.mlx_ptr, data.mlx_win);
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

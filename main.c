#include "cub3d.h"
#include "unistd.h"

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
	{
		ray_draw(data);
		draw_mini_map(data, 0 , 0);
	}
		
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
	data->map_checker = NULL;
	data->map = NULL;
	data->new_map = NULL;
	data->floor = NULL;
	data->ceiling = NULL;
	data->no_texture = NULL;
	data->so_texture = NULL;
	data->we_texture = NULL;
	data->ea_texture = NULL;
	data->floor_parse = NULL;
	data->ceiling_parse = NULL;
}

void	init_image(t_data *data)
{
	textures_check(data);
	data->img_2d.width = (data->width * TILE_SIZE);
	data->img_2d.height = (data->height * TILE_SIZE);
	data->img_2d.img = mlx_new_image(data->mlx_ptr, data->img_2d.width,
			data->img_2d.height);
	if (!data->img_2d.img)
		error_msg("Error: NO enough memmory 2d");
	data->img_2d.img_data = mlx_get_data_addr(data->img_2d.img,
			&data->img_2d.bits_per_pixel, &data->img_2d.size_line,
			&data->img_2d.endian);
	data->img_3d.img = mlx_new_image(data->mlx_ptr, data->img_3d.width,
			data->img_3d.height);
	if (!data->img_3d.img)
		error_msg("Error: NO enough memmory 3d");
	data->img_3d.img_data = mlx_get_data_addr(data->img_3d.img,
			&data->img_3d.bits_per_pixel, &data->img_3d.size_line,
			&data->img_3d.endian);
	ground_draw(data);
	ray_draw(data);
	draw_mini_map(data, 0 , 0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		error_msg("finahiya lmap!!");
	game_init(&data);
	map_parsing(&data, av);
	get_player_position(&data);
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3d");
	init_image(&data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_pressed, &data);
	mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, key_released, &data);
	mlx_loop_hook(data.mlx_ptr, game_render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

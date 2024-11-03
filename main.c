#include "cub3d.h"
#include "unistd.h"

int game_render(t_data *data)
{
	double old_x;
	double old_y;
	double old_angle;

	// TODO: animated sprite
	// TODO: Doors which can open and close.
	old_x = data->p.x;
	old_y = data->p.y;
	old_angle = data->p.angle;
	update_player_rotation(data);
	update_player_position(data);
	if (!(old_x == data->p.x && old_y == data->p.y && old_angle == data->p.angle))
		ray_draw(data); 
	// draw_mini_map(data, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img_3d.img, 0, 0);
	return (0);
}

int game_init(t_data *data)
{
	data->img_2d.width = (data->width * TILE_SIZE);
	data->img_2d.height = (data->height * TILE_SIZE);
	// image deminsion
	data->img_3d.width = WINDOW_WIDTH;
	data->img_3d.height = WINDOW_HEIGHT;
	// mini map
	data->mini_map.width = 	320;
	data->mini_map.height = 180;
	// move
	data->p.r = 2;
	data->p.speed = 0;
	data->key.key_a = 0;
	data->key.key_s = 0;
	data->key.key_d = 0;
	data->key.key_w = 0;
	data->p.angle = 270 * (PI_180 / 180);
	return (0);
}

void set_player_position(t_data *game, int row, int col, double angle)
{
	game->p.x = col *TILE_SIZE + TILE_SIZE / 2;
	game->p.y = row *TILE_SIZE + TILE_SIZE / 2;
	game->p.angle = angle;
}

void get_player_position(t_data *game)
{
	int row;
	int col;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'W')
				set_player_position(game, row, col, PI_180);
			else if (game->map[row][col] == 'N')
				set_player_position(game, row, col, PI_270);
			else if (game->map[row][col] == 'E')
				set_player_position(game, row, col, 0);
			else if (game->map[row][col] == 'S')
				set_player_position(game, row, col, PI_90);
			col++;
		}
		row++;
	}
}

t_data	initialize_variables()
{
	t_data	data;

	data = (t_data){0};
	data.map_checker = NULL;
	data.map = NULL;
	data.new_map = NULL;
	data.floor = NULL;
	data.ceiling = NULL;
	data.no_texture = NULL;
	data.so_texture = NULL;
	data.we_texture = NULL;
	data.ea_texture = NULL;
	data.floor_parse = NULL;
	data.ceiling_parse = NULL;
	return (data);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		error_msg("finahiya lmap!!");

	t_data data;

	data = initialize_variables();
	// TODO: PARSING
	map_parsing(&data, av);
	game_init(&data);
	get_player_position(&data);
	data.mlx_ptr = mlx_init();
	textures_check(&data);
	data.mlx_win = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");

	///// MAP 2D IMAGE 
	data.img_2d.img = mlx_new_image(data.mlx_ptr, data.img_2d.width, data.img_2d.height);
	data.img_2d.img_data = mlx_get_data_addr(data.img_2d.img, &data.img_2d.bits_per_pixel, &data.img_2d.size_line, &data.img_2d.endian);
	ground_draw(&data);
	//// MAP 3D IMAGE
	data.img_3d.img = mlx_new_image(data.mlx_ptr, data.img_3d.width, data.img_3d.height);
	data.img_3d.img_data = mlx_get_data_addr(data.img_3d.img, &data.img_3d.bits_per_pixel, &data.img_3d.size_line, &data.img_3d.endian);
	ray_draw(&data);

	//// KEY_PRESS AND KEY_RELEASE
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_pressed, &data);
	mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, key_released, &data);
	//  mlx_key_hook(data.mlx_win, print_key_press, &data);
	mlx_loop_hook(data.mlx_ptr, game_render, &data);
	mlx_loop(data.mlx_ptr);

	return (0);
}


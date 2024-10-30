#include "cub3d.h"

int game_render(t_data *data)
{
	// TODO: animated sprite
	// TODO: Doors which can open and close.
	clear_image(&(data->img_3d), data->ceiling_color);
	draw_floor(&(data->img_3d), data->floor_color);
	clear_image(&(data->img_2d), COLOR_BLACK);
	update_player_rotation(data);
   	update_player_position(data);
   	ground_draw(data);
	player_draw(data);
	ray_draw(data);
	draw_line(data, (data->p.x + 20 * cos(data->p.angle)), (data->p.y + 20 * sin(data->p.angle)));
	draw_mini_map(data, 0, 0);
   	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img_3d.img, 0, 0);
   return (0);
}

int game_init(t_data *data)
{
	data->img_2d.width = (data->widht * TILE_SIZE);
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

void	get_player_position(t_data *game)
{
	int row;
	int col;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'W' || game->map[row][col] == 'N' || game->map[row][col] == 'E' || game->map[row][col] == 'S')
			{
				if (game->map[row][col] == 'W')
				{
					game->p.x = (col * TILE_SIZE) + (TILE_SIZE / 2);
					game->p.y = (row * TILE_SIZE)+ (TILE_SIZE / 2);
					game->p.angle -= PI_90;
				}
				else if (game->map[row][col] == 'N')
				{
					game->p.x = (col * TILE_SIZE) + (TILE_SIZE / 2);
					game->p.y = (row * TILE_SIZE)+ (TILE_SIZE / 2);
					game->p.angle = 270 * (PI_180 / 180);
				}
				else if (game->map[row][col] == 'E')
				{
					game->p.x = (col * TILE_SIZE) + (TILE_SIZE / 2);
					game->p.y = (row * TILE_SIZE)+ (TILE_SIZE / 2);
					game->p.angle += PI_90;
				}
				else if (game->map[row][col] == 'S')
				{
					game->p.x = (col * TILE_SIZE) + (TILE_SIZE / 2);
					game->p.y = (row * TILE_SIZE)+ (TILE_SIZE / 2);
					game->p.angle += PI_180;
				}
				return ;
			}
			col++;
		}
		col = 0;
		row++;
	}
}

t_data	initialize_variables()
{
	t_data	game;

	game = (t_data){0};
	return (game);
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
	data.mlx_win = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	textures_check(&data);

	///// MAP 2D IMAGE 
	data.img_2d.img = mlx_new_image(data.mlx_ptr, data.img_2d.width, data.img_2d.height);
	data.img_2d.img_data = mlx_get_data_addr(data.img_2d.img, &data.img_2d.bits_per_pixel, &data.img_2d.size_line, &data.img_2d.endian);
	//// MAP 3D IMAGE
	data.img_3d.img = mlx_new_image(data.mlx_ptr, data.img_3d.width, data.img_3d.height);
	data.img_3d.img_data = mlx_get_data_addr(data.img_3d.img, &data.img_3d.bits_per_pixel, &data.img_3d.size_line, &data.img_3d.endian);

	//// KEY_PRESS AND KEY_RELEASE
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_pressed, &data);
	mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, key_released, &data);
	//  mlx_key_hook(data.mlx_win, print_key_press, &data);
	mlx_loop_hook(data.mlx_ptr, game_render, &data);
	mlx_loop(data.mlx_ptr);

	return (0);
}


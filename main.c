#include "cub3d.h"

char *mapi[] = {
	"111111111111111",
	"100000000000001",
	"101111110000001",
	"100000000000001",
	"100000001111111",
	"100000000000001",
	"100000110100001",
	"100000110000001",
	"100100000000001",
	"100000000100001",
	"111111111111111",
   NULL,
};




int game_render(t_data *data)
{
	clear_image(&(data->img_3d), COLOR_GREEN);
	clear_image(&(data->img_2d), COLOR_BLACK);
	update_player_rotation(data);
   update_player_position(data);
   ground_draw(data);
	player_draw(data);
	ray_draw(data);
	// draw_line(data, (data->p.x + 20 * cos(data->p.angle)), (data->p.y + 20 * sin(data->p.angle)));
   mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img_3d.img, 0, 0);
   mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img_2d.img, 0, 0);

   return (0);
}
int game_init(t_data *data)
{
	data->img_2d.width = (NUM_TILES_WIDTH * TILE_SIZE);
	data->img_2d.height = (NUM_TILES_HEIGHT * TILE_SIZE);
	// image deminsion
	data->img_3d.width = WINDOW_WIDTH;
	data->img_3d.height = WINDOW_HEIGHT;
	// // mini map
	data->mini_map.width =  320;
	data->mini_map.height = 180;
	// 
	data->p.ray = NULL;
	data->p.x = data->img_2d.width / 2;
	data->p.y = data->img_2d.height / 2;
	data->p.r = 2;
	data->p.speed = 0;
	data->key.key_a = 0;
	data->key.key_s = 0;
	data->key.key_d = 0;
	data->key.key_w = 0;
	data->p.angle = 270 * (PI_180 / 180 );

}

int	main(void)
{
	t_data data;

	data.map = mapi;
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	game_init(&data);
	
	///// MAP 2D IMAGE 
	data.img_2d.img = mlx_new_image(data.mlx_ptr, data.img_2d.width, data.img_2d.height);
	data.img_2d.img_data = mlx_get_data_addr(data.img_2d.img, &data.img_2d.bits_per_pixel, &data.img_2d.size_line, &data.img_2d.endian);
	//// MAP 3D IMAGE
	data.img_3d.img = mlx_new_image(data.mlx_ptr, data.img_3d.width, data.img_3d.height);
	data.img_3d.img_data = mlx_get_data_addr(data.img_3d.img, &data.img_3d.bits_per_pixel, &data.img_3d.size_line, &data.img_3d.endian);
	/// MINI MAP
	data.mini_map.img = mlx_new_image(data.mlx_ptr, data.mini_map.width, data.mini_map.height);
	data.mini_map.img_data = mlx_get_data_addr(data.mini_map.img, &data.mini_map.bits_per_pixel, &data.mini_map.size_line, &data.mini_map.endian);
	// //// KEY_PRESS AND KEY_RELEASE
	
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_pressed, &data);
	mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, key_released, &data);
	//  mlx_key_hook(data.mlx_win, print_key_press, &data);
	mlx_loop_hook(data.mlx_ptr, game_render, &data);
	mlx_loop(data.mlx_ptr);

	return (0);
}


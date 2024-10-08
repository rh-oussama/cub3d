#include "cub3d.h"

char *mapi[] = {
	"111111111111111",
	"100000000000001",
	"101111110000001",
	"100000000000001",
	"100000001111111",
	"100000000000001",
	"100000100100001",
	"100000000000001",
	"100100001000001",
	"100000000100001",
	"111111111111111",
   NULL,
};




int game_render(t_data *data)
{
	printf("px: %f, py: %f | angle: %f\n",data->p.x, data->p.y, data->p.ray.angle);
   clear_image(data);
	update_player_rotation(data);
   update_player_position(data);
   ground_draw(data);
	player_draw(data);
	// draw_line(data, data->p.x + (50 * cos(data->p.ray.angle)), data->p.y + (50 * sin(data->p.ray.angle)));


	ray_draw(data);
   mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.img, 0, 0);

   return (0);
}
int game_init(t_data *data)
{
	data->p.x = 263.651521; //WINDOW_WIDTH / 2;
	data->p.y = 302.326583; //WINDOW_HEIGHT / 2;
	data->p.r = 3;
	data->p.speed = 0;
	data->key.key_a = 0;
	data->key.key_s = 0;
	data->key.key_d = 0;
	data->key.key_w = 0;
	data->p.ray.angle = 5.735152;//45 * (PI_180 / 180);

}

int	main(void)
{
	t_data data;

	data.map = mapi;
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "hello");
	game_init(&data);

	data.img.img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.img_data = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.size_line, &data.img.endian);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_pressed, &data);
	mlx_hook(data.mlx_win, KeyRelease, KeyReleaseMask, key_released, &data);

	//  mlx_key_hook(data.mlx_win, print_key_press, &data);
	mlx_loop_hook(data.mlx_ptr, game_render, &data);
	mlx_loop(data.mlx_ptr);

	return (0);
}


#include "cub3d.h"

int game_render(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	return (0);
}
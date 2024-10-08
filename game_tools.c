#include "cub3d.h"

int	get_pixel_index(t_data *data, int x, int y)
{
	int byte_in_pixel;
	int byte_in_line;

	byte_in_pixel = data->img.bits_per_pixel / 8;
	byte_in_line = data->img.size_line;
	return (y * byte_in_line) + (x * byte_in_pixel);
}

void	set_pixel_color(t_data *data, int x, int y, int color)
{
	int pixel;

	x = x * SCALE;
	y = y * SCALE;
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return ;

	pixel = get_pixel_index(data, x, y);
	data->img.img_data[pixel] = color & 0xFF;             
	data->img.img_data[pixel + 1] = (color >> 8) & 0xFF;
	data->img.img_data[pixel + 2] = (color >> 16) & 0xFF;
	data->img.img_data[pixel + 3] = (color >> 24) & 0xFF;
}

char	get_type(t_data *data, int pixel_x, int pixel_y)
{
	int	map_x;
	int	map_y;

	map_x = floor(pixel_x / (TILE_SIZE));
	map_y = floor(pixel_y / (TILE_SIZE));
	// printf("")

	// return ('1');
	if (map_y < 0 || map_x < 0 || map_x >= WINDOW_WIDTH / TILE_SIZE || map_y >= WINDOW_HEIGHT / TILE_SIZE)
		return ('1');
	if (data->map[map_y][map_x] == '1')
		return ('1');
	else
		return ('0');
}
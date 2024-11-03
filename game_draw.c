#include "cub3d.h"

void	clear_image(t_img *img, unsigned int COLOR)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			set_pixel_color(img, x, y, COLOR);
			x++;
		}
		y++;
	}
}
void	draw_floor(t_img *img, unsigned int COLOR)
{
	int	x;
	int	y;

	x = 0;
	y = img->height / 2;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			set_pixel_color(img, x, y, COLOR);
			x++;
		}
		y++;
	}
}

void	fill_tail(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE - 1)
	{
		j = 0;
		while (j < TILE_SIZE - 1)
		{
			set_pixel_color(&(data->img_2d), x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	ground_draw(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_GREEN);
			else if (data->map[y][x] == '0' || data->map[y][x] == 'W' || data->map[y][x] == 'N' || data->map[y][x] == 'E' || data->map[y][x] == 'S')
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_WHITE);
			else if (data->map[y][x] == 'D')
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_MAGENTA);
			x++;
		}
		y++;
	}
}

void	player_draw(t_data *data)
{
	int	x;
	int	y;

	x = data->p.x - data->p.r;
	while (x <= data->p.x + data->p.r)
	{
		y = data->p.y - data->p.r;
		while (y <= data->p.y + data->p.r)
		{
			set_pixel_color(&(data->img_2d), x, y, COLOR_BLUE);
			y++;
		}
		x++;
	}
}

void draw_line(t_data *data)
{
	double x;
	double y;
	int i;
	
	i = 0;
	x = data->p.x;
	y = data->p.y;
	while (i < RAW_SIZE)
	{
		x += cos(data->p.angle);
		y += sin(data->p.angle);
		set_pixel_color(&data->img_2d, (int)x, (int)y, COLOR_RED);
		i++;
	}
}

void draw_mini_map(t_data *data, int x, int y)
{
	int	start_x;
	int	start_y;
	int	color;

	start_x = (int) data->p.x - (MINI_WIDTH / 2);
	start_y = (int) data->p.y - (MINI_HEIGHT / 2);
	y = 0;
	while (y < MINI_HEIGHT)
	{
		x = 0;
		while (x < MINI_WIDTH)
		{
			color = get_pixel_color(data, start_x + x, start_y + y);
			set_pixel_color(&data->img_3d,x, y, color);
			x++;
		}
		y++;
	}
}

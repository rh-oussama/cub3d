#include "cub3d.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	clear_image(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			set_pixel_color(data, x, y, 0x000000);
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
	while (i < TILE_SIZE - 1) // i did -1 to not drow last pixel so the cub show
	{
		j = 0;
		while (j < TILE_SIZE - 1)
		{
			set_pixel_color(data, x + j, y + i, color);
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
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_BLACK);
			else
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_WHITE);
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
			set_pixel_color(data, x, y, COLOR_RED);
			y++;
		}
		x++;
	}
}

void	draw_vertical_horizontal(t_data *data, int x2, int y2)
{
	if (x2 == data->p.x)
	{
		while (y2 != data->p.y)
		{
			set_pixel_color(data, x2, y2, COLOR_RED);
			if (y2 > data->p.y)
				y2--;
			else
				y2++;
		}
		return ;
	}
	if (y2 == data->p.y)
	{
		while (x2 != data->p.x)
		{
			set_pixel_color(data, x2, y2, COLOR_RED);
			if (x2 > data->p.x)
				x2--;
			else
				x2++;
		}
		return ;
	}
}

/* Line Equation y = mx + b */
void	draw_line(t_data *data, int x2, int y2)
{
	double	m;
	double	b;
	int		x;
	int		y;

	if (y2 == data->p.y || x2 == data->p.x)
	{
		draw_vertical_horizontal(data, x2, y2);
		return ;
	}
	m = (float)(y2 - data->p.y) / (float)(x2 - data->p.x);
	b = data->p.y - m * data->p.x;
	if (abs(x2 - data->p.x) > abs(y2 - data->p.y))
	{
		x = data->p.x;
		while (x != x2)
		{
			y = (int)(m * x + b);
			set_pixel_color(data, x, y, COLOR_RED);
			if (x2 > data->p.x)
				x += 1;
			else
				x += -1;
		}
	}
	else
	{
		y = data->p.y;
		while (y != y2)
		{
			x = (int)((y - b) / m);
			set_pixel_color(data, x, y, COLOR_RED);
			if (y2 > data->p.y)
				y += 1;
			else
				y += -1;
		}
	}
}

void	ray_draw(t_data *data)
{
	double	*xyd;
	double	degree_increment;
	double	start_angle;
	double	end_angle;
	double	angle;

	degree_increment = (FIELD_OF_VIEW_ANGLE / WINDOW_WIDTH);
	start_angle = data->p.ray.angle - (FIELD_OF_VIEW_ANGLE / 2);
	end_angle = data->p.ray.angle + (FIELD_OF_VIEW_ANGLE / 2);
	if (start_angle < 0)
		start_angle += PI_360;
	if (end_angle >= PI_360)
		end_angle -= PI_360;
	angle = start_angle;
	if (start_angle > end_angle)
	{
		while (angle < PI_360)
		{
			xyd = best_intersaction(data, angle);
			draw_line(data, (int)xyd[0], (int)xyd[1]);
			free(xyd);
			angle += degree_increment;
		}
		angle = 0;
	}
	while (angle <= end_angle)
	{
		xyd = best_intersaction(data, angle);
		draw_line(data, (int)xyd[0], (int)xyd[1]);
		free(xyd);
		angle += degree_increment;
	}
}

// if (data->p.ray.angle == M_PI_2 || data->p.ray.angle == 3 * M_PI_2)
// {
// 	xstep = 0;
// 	ystep = (data->p.ray.angle == M_PI_2) ? TILE_SIZE : -TILE_SIZE;
// }
// else
// {
// 	xstep = (data->p.ray.angle > M_PI_2 && data->p.ray.angle < 3 * M_PI_2) ?
// 		-tile_size : tile_size;
// 	ystep = xstep * tan(data->p.ray.angle);
// }
// // Print the first intersection
// printf("Intersection 1: x = %d, y = %d | angle = %f\n", (int)x, (int)y,
// 	data->p.ray.angle);
// // Calculate and print the next intersection
// for (int i = 0; i < 1; i++)
// {
// 	x += xstep;
// 	y += ystep;
// 	printf("Intersection %d: x = %d, y = %d | angle = %f\n", i + 2, (int)x,
// 		(int)y, data->p.ray.angle);
// }
// Draw the line if within the threshold
// ===================================

// /* cercle  Equation (x−h)^ + (y−k)^ <= r^ */
// void	player_draw(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = data->p.x - data->p.r;
// 	while (x <= data->p.x + data->p.r)
// 	{
// 		y = data->p.y - data->p.r;
// 		while (y <= data->p.y + data->p.r)
// 		{
// 			printf("x: %d | y: %d\n", x, y);
// 			if (pow(x - data->p.x, 2) + pow(y - data->p.y, 2) <= pow(data->p.r,
// 					2))
// 				set_M_xel_color(data, x, y, COLOR_RED);
// 			y++;
// 		}
// 		x++;
// 	}
// }

// ===================================

void	bresenham_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	x0 = data->p.x;
	y0 = data->p.y;
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		printf("x0: %d | y0: %d\n", x0, y0);
		set_pixel_color(data, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
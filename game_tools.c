/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:24:56 by oussama           #+#    #+#             */
/*   Updated: 2024/10/28 08:30:48 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	double	result;

	result = fmod(angle, PI_360);
	if (result < 0)
		result += PI_360;
	return (result);
}

int	is_wall(t_data *data, double *xyd, double angle, char type)
{
	double	x;
	double	y;

	x = xyd[0];
	y = xyd[1];
	if ((type == 'H') && (angle >= PI_180 && angle <= 2 * PI_180))
		y -= 1;
	if ((type == 'V') && (angle >= PI_90 && angle <= PI_270))
		x -= 1;
	if (get_type(data, x, y) == '1')
		return (1);
	return (0);
}

int	get_pixel_index(t_img *img, int x, int y)
{
	int	byte_in_pixel;
	int	byte_in_line;

	byte_in_pixel = img->bits_per_pixel / 8;
	byte_in_line = img->size_line;
	return ((y * byte_in_line) + (x * byte_in_pixel));
}

void	set_pixel_color(t_img *img, int x, int y, int color)
{
	int	pixel;


	if (x < 0 || x > img->width || y < 0 || y > img->height)
		return ;
	pixel = get_pixel_index(img, x, y);
	img->img_data[pixel] = color & 0xFF;
	img->img_data[pixel + 1] = (color >> 8) & 0xFF;
	img->img_data[pixel + 2] = (color >> 16) & 0xFF;
	img->img_data[pixel + 3] = (color >> 24) & 0xFF;
}

char	get_type(t_data *data, double pixel_x, double pixel_y)
{
	int	map_x;
	int	map_y;

	map_x = floor(pixel_x / TILE_SIZE);
	map_y = floor(pixel_y / TILE_SIZE);
	if (map_y < 0 || map_x < 0 || map_x >= data->img_2d.width / TILE_SIZE
		|| map_y >= data->img_2d.height / TILE_SIZE)
		return ('1');
	if (data->map[map_y][map_x] == '1')
		return ('1');
	else
		return ('0');
}

char	get_type_v2(t_data *data, double pixel_x, double pixel_y)
{
   int	map_x;
   int	map_y;
	double new_pixel_x;
	double new_pixel_y;
   double angle;
   double radian;

	angle = 0;
   while (angle < 360)
   {
		radian = angle * PI_180 / 180.0;
		new_pixel_x = pixel_x + PIXELS_AHEAD * cos(radian);
		new_pixel_y = pixel_y + PIXELS_AHEAD * sin(radian);
      map_x = floor(new_pixel_x / TILE_SIZE);
      map_y = floor(new_pixel_y / TILE_SIZE);
      if (map_y < 0 || map_x < 0 || map_x >= data->img_2d.width / TILE_SIZE
            || map_y >= data->img_2d.height / TILE_SIZE)
      {
			angle += 1;
			return ('1');
		}
		if (data->map[map_y][map_x] == '1')
			return ('1');
		angle += 1;
   }
   return ('0');
}


void add_ray(t_ray *ray, double angle, double *xyd, char type)
{
	ray->x = xyd[0];
	ray->y = xyd[1];
	ray->angle = angle;
	ray->distance = xyd[2];
	ray->hit_horizontal = 0;
	if (type == 'h')
		ray->hit_horizontal = 1;
	ray->looking_down = 0;
	if (angle >= 0 && angle <= PI_180)
		ray->looking_down = 1;
	ray->looking_left = 0;
	if (angle >= PI_90 && angle <= PI_270)
		ray->looking_left = 1;	
}

double distance(double x1 , double y1, double x2, double y2)
{
	double distance;
	
	distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return (distance);
	
}

int get_pixel_color(t_data *data, int x, int y)
{
	int	index;
	int	*buffer;
   if (x < 0 || x >= data->img_2d.width || y < 0 || y >= data->img_2d.height)
      return COLOR_BLACK;

	index = get_pixel_index(&data->img_2d, x, y);
   buffer = (int *)data->img_2d.img_data;
   
	return buffer[index / 4];
}

void	error_msg(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:24:56 by oussama           #+#    #+#             */
/*   Updated: 2024/10/13 16:48:27 by oussama          ###   ########.fr       */
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

t_ray	*add_ray_helper(double angle, double *xyd, char type)
{
	t_ray	*new_ray;

	new_ray = (t_ray	*)malloc(sizeof(t_ray));
	if (!new_ray)
		return NULL;
	new_ray->x = xyd[0];
	new_ray->y = xyd[1];
	new_ray->angle = angle;
	new_ray->distance = xyd[2];
	new_ray->hit_horizontal = 0;
	if (type == 'h')
		new_ray->hit_horizontal = 1;
	new_ray->looking_down = 0;
	if (angle >= 0 && angle <= PI_180)
		new_ray->looking_down = 1;
	new_ray->looking_left = 0;
	if (angle >= PI_90 && angle <= PI_270)
		new_ray->looking_left = 1;
	new_ray->next = NULL;

	return new_ray;
}

void add_ray(t_data *data, double angle, double *xyd, char type)
{
	t_ray	*tmp;
	t_ray	*new_ray;

	tmp = data->p.ray;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new_ray = add_ray_helper(angle, xyd, type);
	if (!new_ray)
		return;
	if (tmp)
		tmp->next = new_ray;
	else
		data->p.ray = new_ray;
}

void free_ray(t_data *data)
{
	t_ray *tmp;
	t_ray *tmp2;
	
	tmp = data->p.ray;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
   }
	data->p.ray = NULL;
}

double distance(double x1 , double y1, double x2, double y2)
{
	double distance;
	
	distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return (distance);
	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:24:56 by oussama           #+#    #+#             */
/*   Updated: 2024/11/10 02:19:04 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_index(t_img *img, int x, int y)
{
	int	byte_in_pixel;
	int	byte_in_line;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	byte_in_pixel = img->bits_per_pixel / 8;
	byte_in_line = img->size_line;
	return ((y * byte_in_line) + (x * byte_in_pixel));
}

void	set_pixel_color(t_img *img, int x, int y, int color)
{
	int	pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = get_pixel_index(img, x, y);
	((int *)(img->img_data))[pixel / 4] = color;
}

char	get_type(t_data *data, double pixel_x, double pixel_y)
{
	int	map_x;
	int	map_y;

	map_x = floor(pixel_x / TILE_SIZE);
	map_y = floor(pixel_y / TILE_SIZE);
	if (map_y < 0 || map_x < 0 || map_y >= data->height
		|| map_x >= (int)ft_strlen(data->map[map_y]))
		return ('1');
	if (map_y < 0 || map_x < 0 || map_x >= data->img_2d.width / TILE_SIZE
		|| map_y >= data->img_2d.height / TILE_SIZE)
		return ('1');
	return (data->map[map_y][map_x]);
}

void	add_ray(t_ray *ray, double angle, double *xyd, char type)
{
	ray->x = xyd[0];
	ray->y = xyd[1];
	ray->type = (char)(int)xyd[3];
	ray->distance = xyd[2];
	ray->angle = angle;
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

int	get_pixel_color(t_data *data, int x, int y)
{
	int	index;
	int	*buffer;

	if (x < 0 || x >= data->img_2d.width || y < 0 || y >= data->img_2d.height)
		return (COLOR_BLACK);
	index = get_pixel_index(&data->img_2d, x, y);
	buffer = (int *)data->img_2d.img_data;
	return (buffer[index / 4]);
}

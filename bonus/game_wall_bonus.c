/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_wall_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 09:31:58 by rh                #+#    #+#             */
/*   Updated: 2024/11/16 08:47:34 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_col(t_texture *texture, int x, int y)
{
	int		color;
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->data + (y * texture->size_line + x * (texture->bpp / 8));
	color = *(int *)pixel;
	return (color);
}

void	draw_wall_helper(t_data *data, t_ray *ray)
{
	t_project	*pro;

	pro = &(data->pr_info);
	pro->proj_plane = (WINDOW_WIDTH / 2) / tan(FIELD_OF_VIEW_ANGLE / 2);
	pro->wall_height = (TILE_SIZE / ray->distance) * pro->proj_plane;
	pro->wall_top = (data->pr_info.project_y) - (pro->wall_height / 2);
	if (ray->hit_horizontal)
		pro->hit_point = ray->x;
	else
		pro->hit_point = ray->y;
	if (ray->type == 'D')
		pro->textures = &data->textures[4];
	else if (ray->looking_down && ray->hit_horizontal)
		pro->textures = &data->textures[2];
	else if (!ray->looking_down && ray->hit_horizontal)
		pro->textures = &data->textures[0];
	else if (ray->looking_left && !ray->hit_horizontal)
		pro->textures = &data->textures[3];
	else if (!ray->looking_left && !ray->hit_horizontal)
		pro->textures = &data->textures[1];
	pro->tex_size = pro->textures->height;
}

void	draw_floor_ceilling(t_data *data, t_project *pro, int x)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	y = 0;
	while (y < pro->wall_top)
	{
		tex_x = (x * data->textures[5].width) / WINDOW_WIDTH;
		tex_y = (y * data->textures[5].height) / (WINDOW_HEIGHT);
		color = get_pixel_col(&data->textures[5], tex_x, tex_y);
		set_pixel_color(&data->img_3d, x, y++, color);
	}
	y = (int)pro->wall_top + (int)pro->wall_height;
	while (y < WINDOW_HEIGHT)
		set_pixel_color(&data->img_3d, x, y++, data->floor_color);
}

void	draw_wall(t_data *data, t_ray *ray, int x)
{
	t_project	*pro;
	int			count;
	int			color;
	int			y;

	draw_wall_helper(data, ray);
	count = 0;
	y = 0;
	pro = &data->pr_info;
	pro->tex_x = ((int)(pro->hit_point * pro->tex_size / TILE_SIZE))
		% pro->tex_size;
	if (pro->wall_height > WINDOW_HEIGHT)
		count = (int)-pro->wall_top;
	while (count <= (int)pro->wall_height && y <= WINDOW_HEIGHT)
	{
		y = pro->wall_top + count;
		if (y >= 0)
		{
			pro->tex_y = (count * pro->tex_size) / pro->wall_height;
			color = get_pixel_col(pro->textures, pro->tex_x, pro->tex_y);
			set_pixel_color(&data->img_3d, x, y, color);
		}
		count++;
	}
	draw_floor_ceilling(data, pro, x);
}

void	ray_draw(t_data *data)
{
	int		i;
	double	angle;

	i = 0;
	angle = data->p.angle - (FIELD_OF_VIEW_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		best_intersaction(data, angle, i);
		if (data->p.ray[i].distance)
			draw_wall(data, &(data->p.ray[i]), i);
		angle += FIELD_OF_VIEW_ANGLE / NUM_RAYS;
		i++;
	}
}

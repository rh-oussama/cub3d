/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:36:39 by rh                #+#    #+#             */
/*   Updated: 2024/11/18 11:00:18 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_door_interaction(t_data *data, int x, int y, char type)
{
	if (type == 'D' || type == 'C')
	{
		data->map[(int)y][(int)x] = '0';
		data->door[(int)y][(int)x] = 'O';
		return (1);
	}
	else if (type == 'O' && !(floor(data->p.x / TILE_SIZE) == (int)x
			&& floor(data->p.y / TILE_SIZE) == (int)y))
	{
		data->map[(int)y][(int)x] = 'D';
		data->door[(int)y][(int)x] = 'C';
		return (1);
	}
	return (0);
}

void	door_mechanism(t_data *data)
{
	int		xy[3];
	char	type;
	int		i;

	i = separate_dist(data);
	xy[2] = TILE_SIZE;
	while (xy[2] > 0)
	{
		xy[0] = floor((data->p.x + cos(data->p.angle) * xy[2]) / TILE_SIZE);
		xy[1] = floor((data->p.y + sin(data->p.angle) * xy[2]) / TILE_SIZE);
		type = data->door[(int)xy[1]][(int)xy[0]];
		if (i >= 2 && handle_door_interaction(data, xy[0], xy[1], type))
		{
			ray_draw(data);
			ground_draw(data);
			draw_mini_map(data, 0, 0);
			return ;
		}
		xy[2]--;
	}
}

void	handle_horizontal_wall_collision(t_data *data, double angle, t_ray *ray)
{
	double	next_x;
	double	speed;

	if (!ray->looking_down)
		speed = -((angle / PI_270) - 1) * (double)(COLLISION_SPEED);
	else
		speed = (((angle / PI_90) - 1) * (double)(COLLISION_SPEED));
	next_x = data->p.x + cos(PI_180) * speed;
	if (is_safe(data, next_x, data->p.y))
		data->p.x = next_x;
}

void	handle_vertical_wall_collision(t_data *data, double angle, t_ray *ray)
{
	double	next_y;
	double	speed;

	if (!ray->looking_left)
		speed = -((angle / PI_180) - 1) * (double)(COLLISION_SPEED / 2.f);
	else
		speed = -(((angle / PI_180) - 1) * (double)(COLLISION_SPEED / 2.f));
	next_y = data->p.y + sin(PI_90) * speed;
	if (is_safe(data, data->p.x, next_y))
		data->p.y = next_y;
}

void	process_wall_collision(t_data *data, double angle)
{
	t_ray	*tmp;

	tmp = &data->p.ray[0];
	best_intersaction(data, angle, 0);
	if (tmp->hit_horizontal)
		handle_horizontal_wall_collision(data, angle, tmp);
	else
		handle_vertical_wall_collision(data, angle, tmp);
}

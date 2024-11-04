/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rh <rh@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:26:53 by oussama           #+#    #+#             */
/*   Updated: 2024/11/04 10:01:54 by rh               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		exit(0);
	else if (keysym == XK_w)
		data->key.key_w = 1;
	else if (keysym == XK_s)
		data->key.key_s = 1;
	else if (keysym == XK_a)
		data->key.key_a = 1;
	else if (keysym == XK_d)
		data->key.key_d = 1;
	else if (keysym == XK_Left)
		data->key.key_left = 1;
	else if (keysym == XK_Right)
		data->key.key_right = 1;
	return (0);
}

int	key_released(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data->key.key_w = 0;
	else if (keysym == XK_s)
		data->key.key_s = 0;
	else if (keysym == XK_a)
		data->key.key_a = 0;
	else if (keysym == XK_d)
		data->key.key_d = 0;
	else if (keysym == XK_Left)
		data->key.key_left = 0;
	else if (keysym == XK_Right)
		data->key.key_right = 0;
	return (0);
}

int is_safe(t_data *data, double x, double y)
{
	double check_x;
	double check_y;
   double angle;
	
	angle = 0;
	while (angle <= PI_360)
	{
		check_x = x + cos(angle) * SAFE_DISTANCE;
      check_y = y + sin(angle) * SAFE_DISTANCE;
      if (get_type(data, check_x, check_y) == '1')
			return 0;
      angle += PI_90;
   }
   return 1;
}

void	move_player(t_data *data, double angle)
{
	double	next_x;
	double	next_y;

	next_x = data->p.x + cos(angle) * PLAYER_SPEED;
	next_y = data->p.y + sin(angle) * PLAYER_SPEED;

	if (is_safe(data, next_x, next_y))
	{
		data->p.x = next_x;
		data->p.y = next_y;
	}
	else
	{
		// TODO: MAKE COLLISION WITH WALL
	}

}

void	update_player_position(t_data *data)
{
	if (data->key.key_w)
		move_player(data, data->p.angle);
	if (data->key.key_s)
		move_player(data, data->p.angle + PI_180);
	if (data->key.key_a)
		move_player(data, data->p.angle - PI_90);
	if (data->key.key_d)
		move_player(data, data->p.angle + PI_90);
}

void	update_player_rotation(t_data *data)
{
	double	angle_increment;

	// TODO: Rotate the point of view with the mouse.
	angle_increment = (PI_180 / 180) * ROTATION_SPEED;
	if (data->key.key_left == 1)
		data->p.angle -= angle_increment;
	if (data->key.key_right == 1)
		data->p.angle += angle_increment;
	data->p.angle = normalize_angle(data->p.angle);
}

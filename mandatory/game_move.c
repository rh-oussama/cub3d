/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:26:53 by oussama           #+#    #+#             */
/*   Updated: 2024/11/10 02:19:04 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		exit_game(data);
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

	angle_increment = (PI_180 / 180) * ROTATION_SPEED;
	if (data->key.key_left == 1)
		data->p.angle -= angle_increment;
	if (data->key.key_right == 1)
		data->p.angle += angle_increment;
	data->p.angle = normalize_angle(data->p.angle);
}

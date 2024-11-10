/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rh <rh@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 09:29:43 by rh                #+#    #+#             */
/*   Updated: 2024/11/10 09:29:44 by rh               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_safe(t_data *data, double x, double y)
{
	double	check_x;
	double	check_y;
	double	angle;

	angle = 0;
	while (angle <= PI_360)
	{
		check_x = x + cos(angle) * SAFE_DISTANCE;
		check_y = y + sin(angle) * SAFE_DISTANCE;
		if (get_type(data, check_x, check_y) == '1')
			return (0);
		angle += PI_90;
	}
	return (1);
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
}

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

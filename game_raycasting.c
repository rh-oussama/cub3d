/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rh <rh@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:31:04 by oussama           #+#    #+#             */
/*   Updated: 2024/11/05 18:58:46 by rh               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* GET HORIZONTAL INTERCEPT AND XSTEP AND YSTEP */
void	get_horizonntal(t_data *data, double angle, double *xy_step,
		double *xy_xintercept)
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;

	yintercept = floor(data->p.y / TILE_SIZE) * TILE_SIZE;
	if (angle > 0 && angle < PI_180)
		yintercept += TILE_SIZE;
	xintercept = data->p.x + (yintercept - data->p.y) / tan(angle);
	xstep = TILE_SIZE / tan(angle);
	ystep = TILE_SIZE;
	if (angle > PI_90 && angle < PI_270)
		xstep = -fabs(xstep);
	else
		xstep = fabs(xstep);
	if (angle > PI_180 && angle < PI_360)
		ystep = -fabs(ystep);
	else
		ystep = fabs(ystep);
	xy_xintercept[0] = xintercept;
	xy_xintercept[1] = yintercept;
	xy_step[0] = xstep;
	xy_step[1] = ystep;
}

/* GET X AND Y FO THE RAY AND DISTANCE */
void	get_horizontal_xyd(t_data *data, double angle, double *xyd)
{
	double	xy_step[2];
	double	xy_intercept[2];

	xyd[0] = -1;
	xyd[1] = -1;
	xyd[2] = -1;
	if (angle != 0 && angle != PI_180)
	{
		get_horizonntal(data, angle, xy_step, xy_intercept);
		xyd[0] = xy_intercept[0];
		xyd[1] = xy_intercept[1];
		while (!is_wall(data, xyd, angle, 'H'))
		{
			xyd[0] += xy_step[0];
			xyd[1] += xy_step[1];
		}
		xyd[2] = sqrt(pow(xyd[0] - data->p.x, 2) + pow(xyd[1] - data->p.y, 2));
	}
}

/*GET VERTICAL INTERCEPT AND XSTEP AND YSTEP */
void	get_vertical(t_data *data, double angle, double *xy_step,
		double *xy_xintercept)
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;

	xintercept = floor(data->p.x / TILE_SIZE) * TILE_SIZE;
	if ((angle >= PI_270 && angle <= PI_360) || (angle >= 0 && angle <= PI_90))
		xintercept += TILE_SIZE;
	yintercept = data->p.y + (xintercept - data->p.x) * tan(angle);
	xstep = TILE_SIZE;
	ystep = TILE_SIZE * tan(angle);
	if (angle > PI_90 && angle < PI_270)
		xstep = -fabs(xstep);
	else
		xstep = fabs(xstep);
	if ((angle > 0 && angle < PI_180))
		ystep = fabs(ystep);
	else
		ystep = -fabs(ystep);
	xy_xintercept[0] = xintercept;
	xy_xintercept[1] = yintercept;
	xy_step[0] = xstep;
	xy_step[1] = ystep;
}

/* GET X AND Y FO THE RAY AND DISTANCE */
void	get_vertical_xyd(t_data *data, double angle, double *xyd)
{
	double	xy_step[2];
	double	xy_intercept[2];

	xyd[0] = -1;
	xyd[1] = -1;
	xyd[2] = -1;
	if (angle != PI_270 && angle != PI_90)
	{
		get_vertical(data, angle, xy_step, xy_intercept);
		xyd[0] = xy_intercept[0];
		xyd[1] = xy_intercept[1];
		while (!is_wall(data, xyd, angle, 'V'))
		{
			xyd[0] += xy_step[0];
			xyd[1] += xy_step[1];
		}
		xyd[2] = sqrt(pow(xyd[0] - data->p.x, 2) + pow(xyd[1] - data->p.y, 2));
	}
}

/* GET THE XY FOR THE LESS DISTANCE RAY */
void	best_intersaction(t_data *data, double angle, int i)
{
	double	xyd_h[4];
	double	xyd_v[4];

	angle = normalize_angle(angle);
	get_horizontal_xyd(data, angle, xyd_h);
	get_vertical_xyd(data, angle, xyd_v);
	xyd_h[2] = xyd_h[2] * cos(angle - data->p.angle);
	xyd_v[2] = xyd_v[2] * cos(angle - data->p.angle);
	if (xyd_h[2] < 0)
		add_ray(&(data->p.ray[i]), angle, xyd_v, 'v');
	else if (xyd_v[2] < 0)
		add_ray(&(data->p.ray[i]), angle, xyd_h, 'h');
	else if (xyd_h[2] < xyd_v[2])
		add_ray(&(data->p.ray[i]), angle, xyd_h, 'h');
	else
		add_ray(&(data->p.ray[i]), angle, xyd_v, 'v');
   
}

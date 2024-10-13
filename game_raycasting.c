/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:31:04 by oussama           #+#    #+#             */
/*   Updated: 2024/10/13 15:01:14 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* GET HORIZONTAL INTERCEPT AND XSTEP AND YSTEP */
void get_horizonntal(t_data *data, double angle, double *xy_step, double *xy_xintercept)
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	/// get the first intrcept with horizontal;
	yintercept = floor(data->p.y / TILE_SIZE) * TILE_SIZE;
	if (angle > 0 && angle < PI_180)
		yintercept += TILE_SIZE;
	xintercept = data->p.x + (yintercept - data->p.y) / tan(angle);
	/// get delat x and delta y
	xstep = TILE_SIZE / tan(angle);
	ystep = TILE_SIZE;
	/// 
	if (angle > PI_90 && angle < PI_270)
		xstep = -fabs(xstep);
	else
		xstep = fabs(xstep);
	if (angle > PI_180 && angle < PI_360)
		ystep = -fabs(ystep);
	else
		ystep = fabs(ystep);
	/// fill the intersept and x and y delta
	xy_xintercept[0] = xintercept;
	xy_xintercept[1] = yintercept;
	xy_step[0] = xstep;
	xy_step[1]  = ystep;
}

/* GET X AND Y FO THE RAY AND DISTANCE */
double *get_horizontal_xyd(t_data *data, double angle)
{
	/// xyd[0]: x cordonitae, xyd[1]: y cordonite, xyd[2]: distance
	double *xyd;
	double xy_step[2];
	double xy_intercept[2];

	xyd = (double *) malloc(3 * sizeof(double));
	if (xyd == NULL)
		return NULL;
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
			xyd[1] +=  xy_step[1];
		}
		xyd[2] = sqrt(pow(xyd[0] - data->p.x, 2) + pow(xyd[1] - data->p.y, 2));
	}
	return (xyd);
}


/*GET VERTICAL INTERCEPT AND XSTEP AND YSTEP */
void get_vertical(t_data *data, double angle, double *xy_step, double *xy_xintercept)
{
	double xintercept;
	double yintercept;
	double xstep;
	double ystep;

	/// get the first intercept with vertical;
	xintercept = floor(data->p.x / TILE_SIZE) * TILE_SIZE;
	if ((angle >= PI_270 && angle <= PI_360) || (angle >= 0 && angle <= PI_90))
		xintercept += TILE_SIZE;
	yintercept = data->p.y + (xintercept - data->p.x) * tan(angle);
	/// get delta x and delta y
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
	/// fill the intercept and x and y delta
	xy_xintercept[0] = xintercept;
	xy_xintercept[1] = yintercept;
	xy_step[0] = xstep;
	xy_step[1] = ystep;
}


/* GET X AND Y FO THE RAY AND DISTANCE */
double *get_vertical_xyd(t_data *data, double angle)
{
	double *xyd;
	double xy_step[2];
	double xy_intercept[2];
	
	xyd = (double *) malloc(3 * sizeof(double));
	if (!xyd)
		return (NULL);
	xyd[0] = -1;
	xyd[1] = -1;
	xyd[2] = -1;
	if (data->p.angle != PI_270 && data->p.angle != PI_90)
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
	return (xyd);
}



/* GET THE XY FOR THE LESS DISTANCE RAY */
void	best_intersaction(t_data *data, double angle)
{
	double *xyd_h;
	double *xyd_v;

	angle = normalize_angle(angle);
	xyd_h = get_horizontal_xyd(data, angle);
	xyd_v = get_vertical_xyd(data, angle);
	if (xyd_h[2] < 0)
		add_ray(data, angle, xyd_v, 'v');
	else if (xyd_v[2] < 0)
		add_ray(data, angle, xyd_h, 'h');
	else if (xyd_h[2] < xyd_v[2])
		add_ray(data, angle, xyd_h, 'h');
	else
		add_ray(data, angle, xyd_v, 'v');
	free(xyd_v);
	free(xyd_h);
}

// /* GET THE XY FOR THE LESS DISTANCE RAY */
// double *best_intersaction(t_data *data, double angle)
// {
// 	double *xyd_h;
// 	double *xyd_v;

// 	angle = normalize_angle(angle);
// 	xyd_h = get_horizontal_xyd(data, angle);
// 	xyd_v = get_vertical_xyd(data, angle);

// 	if (xyd_h[2] < 0)
// 		return (free(xyd_h), xyd_v);
// 	else if (xyd_v[2] < 0)
// 		return (free(xyd_v), xyd_h);
// 	else if (xyd_h[2] < xyd_v[2])
// 		return (free(xyd_v), xyd_h);
// 	else
// 		return (free(xyd_h), xyd_v);
// }

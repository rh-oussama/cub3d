#include "cub3d.h"

double normalize_angle(double angle)
{
   double result;
	
	result = fmod(angle, PI_360);
   if (result < 0)
		result += PI_360;
   return result;
}

int is_wall(t_data *data, double *xyd, double angle, char type)
{
	double x;
	double y;

	x = xyd[0];
	y = xyd[1];
	if ((type == 'H') && (angle >= PI_180 && angle <= 2 * PI_180))
		y -= 1;
	if ((type == 'V') && (angle >= PI_90 && angle <= PI_270))
		x -= 1;
	if (get_type(data, x, y) == '1')
		return 1;
	return 0;
	
	
}

/* GET HORIZONTAL INTERCEPT AND XSTEP AND YSTEP */
void get_horizonntal(t_data *data, double angle)
{
	double xintercept;
	double yintercept;
	double xstep;
	double ystep;

	/// get the first intrcept with horizontal;
	yintercept = floor(data->p.y / TILE_SIZE) * TILE_SIZE;
	if (angle > 0 && angle < PI_180)
		yintercept += TILE_SIZE;
	xintercept = data->p.x + (yintercept - data->p.y) / tan(angle);
	
	
	/// get delat x and delta y
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

	/// fill the intersept and x and y delta
	data->p.ray.xintercept = xintercept;
	data->p.ray.yintercept = yintercept;
	data->p.ray.xstep = xstep;
	data->p.ray.ystep = ystep;
}

/*GET VERTICAL INTERCEPT AND XSTEP AND YSTEP */
void get_vertical(t_data *data, double angle)
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
	data->p.ray.xintercept = xintercept;
	data->p.ray.yintercept = yintercept;
	data->p.ray.xstep = xstep;
	data->p.ray.ystep = ystep;
}

/* GET X AND Y FO THE RAY AND DISTANCE */
double *get_horizontal_xyd(t_data *data, double angle)
{
	/// xyd[0]: x cordonitae, xyd[1]: y cordonite, xyd[2]: distance
	double *xyd;

	xyd = (double *)malloc(3 * sizeof(double));
	if (xyd == NULL)
		return NULL;
	xyd[0] = -1;
	xyd[1] = -1;
	xyd[2] = -1;
	if (angle != 0 && angle != PI_180)
	{
		get_horizonntal(data, angle);
		xyd[0] = data->p.ray.xintercept;
		xyd[1] = data->p.ray.yintercept;
		while (!is_wall(data, xyd, angle, 'H'))
		{
			xyd[0] += data->p.ray.xstep;
			xyd[1] += data->p.ray.ystep;
		}
		xyd[2] = sqrt(pow(xyd[0] - data->p.x, 2) + pow(xyd[1] - data->p.y, 2));
	}
	return (xyd);
}

/* GET X AND Y FO THE RAY AND DISTANCE */
double *get_vertical_xyd(t_data *data, double angle)
{
	double *xyd;

	xyd = (double *) malloc(3 * sizeof(double));
	if (!xyd)
		return (NULL);
	xyd[0] = -1;
	xyd[1] = -1;
	xyd[2] = -1;
	if (data->p.ray.angle != PI_270 && data->p.ray.angle != PI_90)
	{
		get_vertical(data, angle);
		xyd[0] = data->p.ray.xintercept;
		xyd[1] = data->p.ray.yintercept;
		while (!is_wall(data, xyd, angle, 'V'))
		{
			xyd[0] += data->p.ray.xstep;
			xyd[1] += data->p.ray.ystep;
		}
		xyd[2] = sqrt(pow(xyd[0] - data->p.x, 2) + pow(xyd[1] - data->p.y, 2));
	}
	return (xyd);
}

/* GET THE XY FOR THE LESS DISTANCE RAY */
double *best_intersaction(t_data *data, double angle)
{
	double *xyd_h;
	double *xyd_v;

	angle = normalize_angle(angle);
	xyd_h = get_horizontal_xyd(data, angle);
	xyd_v = get_vertical_xyd(data, angle);

	if (xyd_h[2] < 0)
		return (free(xyd_h), xyd_v);
	else if (xyd_v[2] < 0)
		return (free(xyd_v), xyd_h);
	else if (xyd_h[2] < xyd_v[2])
		return (free(xyd_v), xyd_h);
	else
		return (free(xyd_h), xyd_v);
}



#include "cub3d.h"

/*GET VERTICAL INTERCEPT AND XSTEP AND YSTEP */
void get_vertical(t_data *data, double angle)
{
	double xintercept;
	double yintercept;
	double xstep;
	double ystep;

	/// get the first intercept with vertical;
	xintercept = floor(data->p.x / TILE_SIZE) * TILE_SIZE - 1;
	if (angle < PI_90 || angle > PI_270)
		xintercept += TILE_SIZE + 1;
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
double *get_vertical_xyd(t_data *data, double angle)
{
	/// xyd[0]: x cordonitae, xyd[1]: y cordonite, xyd[2]: distance
	double *xyd;

	xyd = (double *)malloc(3 * sizeof(double));
	if (xyd == NULL)
		return NULL;
	xyd[0] = -1;
	xyd[1] = -1;
	xyd[2] = -1;
	if (data->p.ray.angle != PI_270 && data->p.ray.angle != PI_90)
	{
		get_vertical(data, angle);
		xyd[0] = data->p.ray.xintercept;
		xyd[1] = data->p.ray.yintercept;
		while (1)
		{
			if (get_type(data, (int)(xyd[0] + data->p.ray.xstep), (int)(xyd[1] + data->p.ray.ystep)) == '1')
				break;
			xyd[0] += data->p.ray.xstep;
			xyd[1] += data->p.ray.ystep;
		}
		xyd[2] = sqrt(pow(xyd[0] - data->p.x, 2) + pow(xyd[1] - data->p.y, 2));
	}
	return (xyd);
}


void get_horizontal(t_data *data, double angle)
{
	double xintercept;
	double yintercept;
	double xstep;
	double ystep;

	// Get the first intercept with horizontal
	yintercept = floor(data->p.y / TILE_SIZE) * TILE_SIZE - 1;
	if (angle > 0 && angle < M_PI)
		yintercept += TILE_SIZE + 1;
	xintercept = data->p.x + (yintercept - data->p.y) / tan(angle);

	// Get delta x and delta y
	ystep = TILE_SIZE;
	xstep = TILE_SIZE / tan(angle);

	printf("ystep: %f, xstep: %f | yintercept: %f, xintercept: %f\n", ystep, xstep, yintercept, xintercept);

	if (angle > M_PI_2 && angle < 3 * M_PI_2)
		xstep = -fabs(xstep);
	else
		xstep = fabs(xstep);
	if (angle > M_PI && angle < 2 * M_PI)
		ystep = -fabs(ystep);
	else
		ystep = fabs(ystep);

	// Fill the intercept and x and y delta
	data->p.ray.xintercept = xintercept;
	data->p.ray.yintercept = yintercept;
	data->p.ray.xstep = xstep;
	data->p.ray.ystep = ystep;
}

double *get_horizontal_xyd(t_data *data, double angle)
{
	// xyd[0]: x coordinate, xyd[1]: y coordinate, xyd[2]: distance
	double *xyd;

	xyd = (double *) malloc(3 * sizeof(double));
	if (xyd == NULL)
		return NULL;

	xyd[0] = -1;
	xyd[1] = -1;
	xyd[2] = -1;

	if (angle != 0 && angle != M_PI)
	{
		get_horizontal(data, angle);
		xyd[0] = data->p.ray.xintercept;
		xyd[1] = data->p.ray.yintercept;
		while (1)
		{
			// Update to use correct X and Y steps
			if (get_type(data, (int)(xyd[0] + data->p.ray.xstep), (int)(xyd[1] + data->p.ray.ystep)) == '1')
				break;
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

	xyd_h = get_horizontal_xyd(data, angle);
	// return (xyd_h);
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



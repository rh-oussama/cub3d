#include "cub3d.h"

int	is_safe(t_data *data, double x, double y)
{
	double	check_x;
	double	check_y;
	double	angle;
	char	type;

	angle = 0;
	while (angle <= PI_360)
	{
		check_x = x + cos(angle) * SAFE_DISTANCE;
		check_y = y + sin(angle) * SAFE_DISTANCE;
		type = get_type(data, check_x, check_y);
		if (type == '1' || type == 'D')
			return (0);
		angle += PI_90 / 4;
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
	char	wall_type;

	x = xyd[0];
	y = xyd[1];
	if ((type == 'H') && (angle >= PI_180 && angle <= 2 * PI_180))
		y -= 1;
	if ((type == 'V') && (angle >= PI_90 && angle <= PI_270))
		x -= 1;
	wall_type = get_type(data, x, y);
	if (wall_type == '1' || wall_type == 'D')
	{
		xyd[3] = (double)wall_type;
		return (1);
	}
	return (0);
}

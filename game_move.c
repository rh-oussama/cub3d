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
		data->key.key_left = 1; // Rotate left
	else if (keysym == XK_Right)
		data->key.key_right = 1; // Rotate right
	// printf("key pressed: %d\n", keysym);
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
	// printf("key released: %d\n", keysym);
	return (0);
}

void	update_player_position(t_data *data)
{
	if (data->key.key_w)
	{
		data->p.x += cos(data->p.ray.angle) * PLAYER_SPEED;
		data->p.y += sin(data->p.ray.angle) * PLAYER_SPEED;
	}
	if (data->key.key_s)
	{
		data->p.x -= cos(data->p.ray.angle) * PLAYER_SPEED;
		data->p.y -= sin(data->p.ray.angle) * PLAYER_SPEED;
	}
	if (data->key.key_a)
	{
		data->p.x += cos(data->p.ray.angle - PI_90) * PLAYER_SPEED;
		data->p.y += sin(data->p.ray.angle - PI_90) * PLAYER_SPEED;
	}
	if (data->key.key_d)
	{
		data->p.x += cos(data->p.ray.angle + PI_90) * PLAYER_SPEED;
		data->p.y += sin(data->p.ray.angle + PI_90) * PLAYER_SPEED;
	}
}

void	update_player_rotation(t_data *data)
{
	const double angle_increment = (PI_180 / 180) * ROTATION_SPEED;

	if (data->key.key_left == 1)
	{
		data->p.ray.angle -= angle_increment;
		if (data->p.ray.angle < 0)
			data->p.ray.angle += 2 * PI_180;
	}

	if (data->key.key_right == 1)
	{
		data->p.ray.angle += angle_increment;
		if (data->p.ray.angle >= 2 * PI_180)
			data->p.ray.angle -= 2 * PI_180;
	}
}
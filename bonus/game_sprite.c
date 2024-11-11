/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 03:25:33 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/11 03:46:15 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_it(int star)
{
	if (star == 0)
		return (1216);
	else if (star == 1)
		return (1152);
	else if (star == 2)
		return (1088);
	else if (star == 3)
		return (1024);
	else
		return (960);
}

int	frame_draw(t_data *game, int frame, int star)
{
	int	color;
	int	sprite_x_offset;
	int	x;
	int	y;

	sprite_x_offset = get_it(star);
	y = 0;
	while (y < game->sprite[frame].height)
	{
		x = 0;
		while (x < game->sprite[frame].width)
		{
			color = get_pixel_drawer(&game->sprite[frame], x, y);
			if (color != -16777216)
			{
				set_pixel_color(&game->img_3d, sprite_x_offset + x, y, color);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	sprite(t_data *data)
{
	double			delta_time;
	static int		frame = 0;
	static int		star = 0;
	static double	frame_timer = 0.0;

	delta_time = 1.0 / 60.0;
	frame_timer += delta_time;
	if (star == 5)
		star = 0;
	if (frame_timer >= 0.3)
	{
		frame = (frame + 1) % 8;
		if (frame == 0)
			star++;
		frame_timer = 0.0;
	}
	frame_draw(data, frame, star);
	return (0);
}

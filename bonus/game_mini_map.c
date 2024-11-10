/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:23:16 by rh                #+#    #+#             */
/*   Updated: 2024/11/10 02:19:04 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * fill_tail - Fills a tile with a specified color.
 *
 * This function fills a tile of size TILE_SIZE with the specified color.
 */
void	fill_tail(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE - 1)
	{
		j = 0;
		while (j < TILE_SIZE - 1)
		{
			set_pixel_color(&(data->img_2d), x + j, y + i, color);
			j++;
		}
		i++;
	}
}

/**
 * ground_draw - Draws the ground based on the map data.
 *
 * This function iterates through the map and fills tiles with different colors
 * based on the map characters ('1', '0', 'W', 'N', 'E', 'S', 'D').
 */
void	ground_draw(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_GREEN);
			else if (data->door && data->door[y][x] == 'O')
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_CYAN);
			else if (data->map[y][x] == '0' || data->map[y][x] == 'W'
				|| data->map[y][x] == 'N' || data->map[y][x] == 'E'
				|| data->map[y][x] == 'S')
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_WHITE);
			else if (data->map[y][x] == 'D')
				fill_tail(data, x * TILE_SIZE, y * TILE_SIZE, COLOR_MAGENTA);
			x++;
		}
		y++;
	}
}

/**
 * player_draw - Draws the player on the map.
 *

	* This function draws a sqaure representing the player
		 at the specified position.
 */
void	player_draw(t_data *data, int xpos, int ypos)
{
	int	x;
	int	y;

	x = xpos - data->p.r;
	while (x <= xpos + data->p.r)
	{
		y = ypos - data->p.r;
		while (y <= ypos + data->p.r)
		{
			set_pixel_color(&(data->img_3d), x, y, COLOR_BLUE);
			y++;
		}
		x++;
	}
}

/**
 * draw_line
	- Draws a line from the player's position in the direction
					 the player's angle.
 *
	* This function draws a line from the player's position in 
				the direction of the player's angle.
 */
void	draw_line(t_data *data, double xpos, double ypos)
{
	int	i;

	i = 0;
	while (i < RAW_SIZE)
	{
		xpos += cos(data->p.angle);
		ypos += sin(data->p.angle);
		set_pixel_color(&data->img_3d, (int)xpos, (int)ypos, COLOR_RED);
		i++;
	}
}

/**
 * draw_mini_map - Draws the mini-map on the screen.
 *
 * This function draws the mini-map on the screen,
	including the player and a line indicating the player's direction.
 */
void	draw_mini_map(t_data *data, int x, int y)
{
	int	start_x;
	int	start_y;
	int	color;

	start_x = (int)data->p.x - (MINI_WIDTH / 2);
	start_y = (int)data->p.y - (MINI_HEIGHT / 2);
	y = 0;
	while (y < MINI_HEIGHT)
	{
		x = 0;
		while (x < MINI_WIDTH)
		{
			color = get_pixel_color(data, start_x + x, start_y + y);
			set_pixel_color(&data->img_3d, x, y, color);
			x++;
		}
		y++;
	}
	player_draw(data, MINI_WIDTH / 2, MINI_HEIGHT / 2);
	draw_line(data, MINI_WIDTH / 2, MINI_HEIGHT / 2);
}

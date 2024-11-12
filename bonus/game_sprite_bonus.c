/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 03:25:33 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/12 20:17:28 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	lenght(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nbr;

	nbr = n;
	len = lenght(nbr);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	if (nbr == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (nbr != 0)
	{
		str[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len--;
	}
	return (str);
}

void scale_and_draw(t_data *game, int frame, int new_width, int new_height)
{
	int	color;
	int	x;
	int	y;
	int	scaled_x;
	int	scaled_y;
	double	scale_x;
	double	scale_y;

	scale_x = (double)new_width / game->first[frame].width;
	scale_y = (double)new_height / game->first[frame].height;

	y = 0;
	while (y < new_height)
	{
		x = 0;
		while (x < new_width)
		{
			scaled_x = x / scale_x;
			scaled_y = y / scale_y;
			color = get_pixel_col(&game->first[frame], scaled_x, scaled_y);
			if (color != -16777216)
				set_pixel_color(&game->img_3d, x + (game->img_3d.width - new_width), y + (game->img_3d.height - new_height), color);
			x++;
		}
		y++;
	}
}

int	frame_draw(t_data *game, int frame)
{
	scale_and_draw(game, frame, 1024 , 576);
	return (0);
}

int	sprite(t_data *data)
{
	double			delta_time;
	static int		frame = 0;
	static double	frame_timer = 0.0;

	delta_time = 1.0 / 30.0;
	frame_timer += delta_time;
	if (frame_timer >= 0.1)
	{
		frame = (frame + 1) % 102;
		frame_timer = 0.0;
	}
	if (data->key.key_k)
		frame_draw(data, frame);
	return (frame);
}

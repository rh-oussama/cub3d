/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 03:25:33 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/18 18:14:07 by alamaoui         ###   ########.fr       */
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

int	frame_draw(t_data *game, t_texture *sprite, int frame)
{
	int	color;
	int	x;
	int	y;

	y = 0;
	while (y < sprite[frame].height)
	{
		x = 0;
		while (x < sprite[frame].width)
		{
			color = get_pixel_col(&sprite[frame], x, y);
			if (color != -16777216)
				set_pixel_color(&game->img_3d, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

int	sprite(t_data *data, t_texture *sprite, int frames)
{
	double			delta_time;
	static int		frames_array[4] = {0, 0, 0, 0};
	int				frame_index;
	int				frame;
	static double	frame_timer = 0.00;

	if (sprite == data->first)
		frame_index = 0;
	else if (sprite == data->second)
		frame_index = 1;
	else if (sprite == data->third)
		frame_index = 2;
	else if (sprite == data->fourth)
		frame_index = 3;
	frame = frames_array[frame_index];
	delta_time = 1.0 / 60.0;
	frame_timer += delta_time;
	if (frame_timer >= 0.06 || frame == 0)
	{
		frame = (frame + 1) % frames;
		frame_timer = 0.0;
	}
	frames_array[frame_index] = frame;
	frame_draw(data, sprite, frame);
	return (frame);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rh <rh@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:36:39 by rh                #+#    #+#             */
/*   Updated: 2024/11/05 20:38:46 by rh               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <string.h>

char	**new_array(char **array)
{
	int		i;
	int		count;
	char	**n_arr;

	count = 0;
	while (array[count])
		count++;
	n_arr = (char **)malloc((count + 1) * sizeof(char *));
	if (!n_arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		n_arr[i] = strdup(array[i]);
		if (!n_arr[i])
		{
			while (i > 0)
				free(n_arr[--i]);
			free(n_arr);
			return (NULL);
		}
		i++;
	}
	n_arr[i] = NULL;
	return (n_arr);
}

int	handle_door_interaction(t_data *data, int x, int y, char type)
{
	if (type == 'D' || type == 'C')
	{
		data->map[(int)y][(int)x] = '0';
		data->door[(int)y][(int)x] = 'O';
		return (1);
	}
	else if (type == 'O' && !(floor(data->p.x / TILE_SIZE) == (int)x
			&& floor(data->p.y / TILE_SIZE) == (int)y))
	{
		data->map[(int)y][(int)x] = 'D';
		data->door[(int)y][(int)x] = 'C';
		return (1);
	}
	return (0);
}

/* TODO: change color if door is open  */
void	door_mechanism(t_data *data)
{
	char	type;
	int		dist;
	int		x;
	int		y;

	dist = 35;
	/// TODO: delete this when merge do it in init
	if (!data->door)
	{
		data->door = new_array(data->map);
		if (!data->door)
			error_msg("No enough memory");
	}
	while (dist > 0)
	{
		x = floor((data->p.x + cos(data->p.angle) * dist) / TILE_SIZE);
		y = floor((data->p.y + sin(data->p.angle) * dist) / TILE_SIZE);
		type = data->door[(int)y][(int)x];
		if (handle_door_interaction(data, x, y, type))
		{
			ray_draw(data);
			// TODO: draw mini map another time to change the color of door
			draw_mini_map(data, 0, 0);
			return ;
		}
		dist--;
	}
}

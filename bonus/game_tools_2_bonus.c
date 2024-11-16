/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_tools_2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 09:32:08 by rh                #+#    #+#             */
/*   Updated: 2024/11/16 07:51:37 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		n_arr[i] = ft_strdup(array[i]);
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

void	get_textures(t_data *game)
{
	game->no_texture = validate_path(game->no_texture, game);
	game->so_texture = validate_path(game->so_texture, game);
	game->we_texture = validate_path(game->we_texture, game);
	game->ea_texture = validate_path(game->ea_texture, game);
}

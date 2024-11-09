/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_map2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:53:01 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/09 23:43:42 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	f(char *trimmed, t_data *data, int *flag)
{
	if (ft_strchr(trimmed, 'F') && ft_strchr(trimmed, ','))
	{
		if (data->floor)
			free(data->floor);
		checker(trimmed, 'F', data);
		data->floor = ft_strdup(trimmed);
		(*flag)++;
	}
}

void	c(char *trimmed, t_data *data, int *flag)
{
	if (ft_strchr(trimmed, 'C') && ft_strchr(trimmed, ','))
	{
		if (data->ceiling)
			free(data->ceiling);
		checker(trimmed, 'C', data);
		data->ceiling = ft_strdup(trimmed);
		(*flag)++;
	}
}

int	allocation_size(t_data *data, int x)
{
	int	lines;
	int	counter;
	int	size;

	counter = 0;
	size = 0;
	lines = x;
	while (data->map_checker[lines])
	{
		if (!ft_strchr(data->map_checker[lines], '1'))
			size++;
		else
			size = 0;
		counter++;
		lines++;
	}
	get_width(data, x);
	data->map = malloc(((counter - size) + 1) * sizeof(char *));
	return (counter - size);
}

void	map(t_data *data, int x, char *trimmed)
{
	int	i;
	int	height;

	i = 0;
	free(trimmed);
	if (!data->no_texture || !data->so_texture || !data->we_texture
		|| !data->ea_texture || !data->floor || !data->ceiling)
		error_msg_2("Missing configuration or order is wrong", data);
	height = allocation_size(data, x);
	while (data->map_checker[x])
	{
		if (i == (height))
			break ;
		data->map[i] = ft_copy(data->map_checker[x], data->width);
		i++;
		x++;
	}
	data->map[i] = NULL;
	data->height = i;
}

void	map_configure(t_data *data, int x, int flag, char *trimmed)
{
	while (data->map_checker[x])
	{
		trimmed = trim(data, flag, x, trimmed);
		if (!ft_strncmp(trimmed, "NO ", 3))
			no(trimmed, data, &flag);
		else if (!ft_strncmp(trimmed, "SO ", 3))
			so(trimmed, data, &flag);
		else if (!ft_strncmp(trimmed, "WE ", 3))
			we(trimmed, data, &flag);
		else if (!ft_strncmp(trimmed, "EA ", 3))
			ea(trimmed, data, &flag);
		else if (ft_strchr(trimmed, 'F') && ft_strchr(trimmed, ','))
			f(trimmed, data, &flag);
		else if (ft_strchr(trimmed, 'C') && ft_strchr(trimmed, ','))
			c(trimmed, data, &flag);
		else if (ft_strchr(data->map_checker[x], '1'))
		{
			map(data, x, trimmed);
			return ;
		}
		else
			line_check(data->map_checker[x], data, trimmed);
		free(trimmed);
		x++;
	}
}

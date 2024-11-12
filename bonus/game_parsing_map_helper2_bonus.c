/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_map_helper2_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:35:28 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/12 04:37:23 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	no(char *trimmed, t_data *data, int *flag)
{
	if (!ft_strncmp(trimmed, "NO ", 3))
	{
		if (data->no_texture)
			free(data->no_texture);
		data->no_texture = ft_strdup(trimmed);
		(*flag)++;
	}
}

void	so(char *trimmed, t_data *data, int *flag)
{
	if (!ft_strncmp(trimmed, "SO ", 3))
	{
		if (data->so_texture)
			free(data->so_texture);
		data->so_texture = ft_strdup(trimmed);
		(*flag)++;
	}
}

void	we(char *trimmed, t_data *data, int *flag)
{
	if (!ft_strncmp(trimmed, "WE ", 3))
	{
		if (data->we_texture)
			free(data->we_texture);
		data->we_texture = ft_strdup(trimmed);
		(*flag)++;
	}
}

void	ea(char *trimmed, t_data *data, int *flag)
{
	if (!ft_strncmp(trimmed, "EA ", 3))
	{
		if (data->ea_texture)
			free(data->ea_texture);
		data->ea_texture = ft_strdup(trimmed);
		(*flag)++;
	}
}

char	*trim(t_data *data, int flag, int x, char *trimmed)
{
	if (flag > 6)
		error_msg_2("Invalid configuration", data);
	trimmed = ft_strtrim(data->map_checker[x]);
	return (trimmed);
}

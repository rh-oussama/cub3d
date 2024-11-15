/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:09 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/15 03:46:52 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*validate_path(char *str, t_data *data)
{
	char	*path;
	char	*tmp;

	tmp = str;
	if (!str)
		error(data);
	if (ft_strncmp(str, "NO", 2) && ft_strncmp(str, "SO", 2) && ft_strncmp(str,
			"EA", 2) && ft_strncmp(str, "WE", 2))
		error(data);
	if (str[2] != ' ')
		error(data);
	str += 3;
	if (!(*str))
		error(data);
	while (*str)
	{
		if (ft_isspace(*str) && *str != '\n')
			error(data);
		str++;
	}
	path = ft_strdup(&(tmp[3]));
	free(tmp);
	return (path);
}

void	get_textures(t_data *game)
{
	game->no_texture = validate_path(game->no_texture, game);
	game->so_texture = validate_path(game->so_texture, game);
	game->we_texture = validate_path(game->we_texture, game);
	game->ea_texture = validate_path(game->ea_texture, game);
}

void	load_textures(t_data *game, t_texture *texture, char *tex_str, int idx)
{
	texture[idx].img = mlx_xpm_file_to_image(game->mlx_ptr, tex_str,
			&texture[idx].width, &texture[idx].height);
	if (texture[idx].img == NULL)
		error(game);
	texture[idx].data = mlx_get_data_addr(texture[idx].img, &texture[idx].bpp,
			&texture[idx].size_line, &texture[idx].endian);
}

void	textures_check(t_data *game)
{
	load_textures(game, game->textures, game->no_texture, 0);
	load_textures(game, game->textures, game->ea_texture, 1);
	load_textures(game, game->textures, game->so_texture, 2);
	load_textures(game, game->textures, game->we_texture, 3);
}

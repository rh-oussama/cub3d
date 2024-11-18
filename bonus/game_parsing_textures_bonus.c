/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_textures_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:09 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/18 06:06:17 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_sprit_path(char *base_path, int index)
{
	char	*final_path;
	char	*nbr;
	char	*tmp;

	tmp = ft_strdup(base_path);
	nbr = ft_itoa(index + 1);
	if (!nbr)
		return (NULL);
	final_path = ft_strjoin(tmp, nbr);
	free(nbr);
	if (!final_path)
		return (NULL);
	final_path = ft_strjoin(final_path, ".xpm");
	return (final_path);
}

void	sprite_textures(t_data *game, t_texture *texture, char *path, int total)
{
	char	*final_path;
	int		i;

	i = 0;
	while (i < total)
	{
		final_path = get_sprit_path(path, i);
		texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, final_path,
				&texture[i].width, &texture[i].height);
		if (!texture[i].img)
		{
			free(final_path);
			error(game);
		}
		texture[i].data = mlx_get_data_addr(texture[i].img, &texture[i].bpp,
				&texture[i].size_line, &texture[i].endian);
		free(final_path);
		i++;
	}
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

void	load_door_ceiling(t_data *game, char *str)
{
	char	*path;
	char	*tmp;

	if (!game || !str)
		return ;
	tmp = ft_strdup(str);
	if (!tmp)
		return ;
	path = ft_strrchr(tmp, '/');
	if (!path)
	{
		game->door_tex = ft_strdup("./textures/door.xpm");
		game->ceiling_tex = ft_strdup("./textures/ceiling.xpm");
		free(tmp);
		return ;
	}
	if (path)
		path[1] = '\0';
	game->door_tex = ft_strdup(tmp);
	game->ceiling_tex = ft_strdup(tmp);
	game->door_tex = ft_strjoin(game->door_tex, "door.xpm");
	game->ceiling_tex = ft_strjoin(game->ceiling_tex, "ceiling.xpm");
	free(tmp);
}

void	textures_check(t_data *game)
{
	loading_bar(game, 1);
	load_door_ceiling(game, game->no_texture);
	load_textures(game, game->textures, game->no_texture, 0);
	load_textures(game, game->textures, game->ea_texture, 1);
	load_textures(game, game->textures, game->so_texture, 2);
	load_textures(game, game->textures, game->we_texture, 3);
	load_textures(game, game->textures, game->door_tex, 4);
	load_textures(game, game->textures, game->ceiling_tex, 5);
	loading_bar(game, 2);
	sprite_textures(game, game->first, "./textures/first/n", 43);
	loading_bar(game, 3);
	sprite_textures(game, game->second, "./textures/second/j", 101);
	loading_bar(game, 4);
	sprite_textures(game, game->third, "./textures/third/s", 14);
	loading_bar(game, 5);
	sprite_textures(game, game->fourth, "./textures/fourth/w", 31);
}

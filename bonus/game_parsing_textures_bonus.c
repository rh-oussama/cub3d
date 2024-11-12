/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_textures_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:09 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/12 09:55:58 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*validate_path(char *str, t_data *data)
{
	char	*path;
	char	*tmp;

	tmp = str;
	if (!str)
		error_msg_2("Invalid configuration (EMPTY)", data);
	if (ft_strncmp(str, "NO", 2) && ft_strncmp(str, "SO", 2) && ft_strncmp(str,
			"EA", 2) && ft_strncmp(str, "WE", 2))
		error_msg_2("Invalid configuration (NO | EA | SO | WE)", data);
	if (str[2] != ' ')
		error_msg_2("Error (NO SPACE BETWEEN PATH AND DIRECTION)", data);
	str += 3;
	if (!(*str))
		error_msg_2("Invalid configuration (EMPTY PATH)", data);
	while (*str)
	{
		if (ft_isspace(*str) && *str != '\n')
			error_msg_2("Invalid configuration (FOUND SPACE IN PATH)", data);
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

void	load_textures(t_data *game, t_texture	*texture, \
								char *tex_str, int idx)
{
	texture[idx].img = mlx_xpm_file_to_image(game->mlx_ptr, tex_str,
			&texture[idx].width, &texture[idx].height);
	if (texture[idx].img == NULL)
	{
		while (idx >= 0)
		{
			mlx_destroy_image(game->mlx_ptr, game->textures[idx].img);
			idx--;
		}
		mlx_destroy_window(game->mlx_ptr, game->mlx_win);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		error_msg_2("Problem in textures", game);
	}
	texture[idx].data = mlx_get_data_addr(texture[idx].img,
			&texture[idx].bpp, &texture[idx].size_line,
			&texture[idx].endian);
}

void	textures_check(t_data *game)
{
	//// wall texture
	load_textures(game, game->textures, game->no_texture, 0);
	load_textures(game, game->textures, game->ea_texture, 1);
	load_textures(game, game->textures, game->so_texture, 2);
	load_textures(game, game->textures, game->we_texture, 3);
	load_textures(game, game->textures, "./textures/door.xpm", 4);
	load_textures(game, game->textures, "./textures/ceiling.xpm", 5);
	//// sprite_texture
	// TODO :: DESTROY WALL TEXTURE IF SPRITE FAIL
	load_textures(game, game->sprite, "./textures/star_sp/img1.xpm", 0);
	load_textures(game, game->sprite, "./textures/star_sp/img2.xpm", 1);
	load_textures(game, game->sprite, "./textures/star_sp/img3.xpm", 2);
	load_textures(game, game->sprite, "./textures/star_sp/img4.xpm", 3);
	load_textures(game, game->sprite, "./textures/star_sp/img5.xpm", 4);
	load_textures(game, game->sprite, "./textures/star_sp/img6.xpm", 5);
	load_textures(game, game->sprite, "./textures/star_sp/img7.xpm", 6);
	load_textures(game, game->sprite, "./textures/star_sp/img8.xpm", 7);
}

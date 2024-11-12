/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_textures_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:09 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/12 20:30:55 by alamaoui         ###   ########.fr       */
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

void	no_image(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 5)
	{
		if (game->textures[i].img == NULL)
		{
			j = 0;
			while (j < 5)
			{
				if (j != i)
					mlx_destroy_image(game->mlx_ptr, game->textures[j].img);
				j++;
			}
			mlx_destroy_window(game->mlx_ptr, game->mlx_win);
			mlx_destroy_display(game->mlx_ptr);
			free(game->mlx_ptr);
			error_msg_2("Problem in textures", game);
		}
		i++;
	}
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

void	main_one(t_data *game)
{
	load_textures(game, game->textures, game->no_texture, 0);
	load_textures(game, game->textures, game->ea_texture, 1);
	load_textures(game, game->textures, game->so_texture, 2);
	load_textures(game, game->textures, game->we_texture, 3);
	load_textures(game, game->textures, "./textures/door.xpm", 4);
	load_textures(game, game->textures, "./textures/ceiling.xpm", 5);
}


void	textures_check(t_data *game)
{
	t_texture	*t;
	int			i;

	i = 0;
	t = game->textures;
	main_one(game);
	sprite_textures(game);
	while (i < 5)
	{
		t[i].data = mlx_get_data_addr(t[i].img, &t[i].bpp, &t[i].size_line,
				&t[i].endian);
		i++;
	}
}

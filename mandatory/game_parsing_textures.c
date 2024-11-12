/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:06:09 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/10 02:19:04 by alamaoui         ###   ########.fr       */
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
	while (i < 4)
	{
		if (game->textures[i].img == NULL)
		{
			j = 0;
			while (j < 4)
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

void	textures_check(t_data *game)
{
	t_texture	*t;

	t = game->textures;
	t[0].img = mlx_xpm_file_to_image(game->mlx_ptr, game->no_texture,
			&t[0].width, &t[0].height);
	t[1].img = mlx_xpm_file_to_image(game->mlx_ptr, game->ea_texture,
			&t[1].width, &t[1].height);
	t[2].img = mlx_xpm_file_to_image(game->mlx_ptr, game->so_texture,
			&t[2].width, &t[2].height);
	t[3].img = mlx_xpm_file_to_image(game->mlx_ptr, game->we_texture,
			&t[3].width, &t[3].height);
	no_image(game);
	t[0].data = mlx_get_data_addr(t[0].img, &t[0].bpp, &t[0].size_line,
			&t[0].endian);
	t[1].data = mlx_get_data_addr(t[1].img, &t[1].bpp, &t[1].size_line,
			&t[1].endian);
	t[2].data = mlx_get_data_addr(t[2].img, &t[2].bpp, &t[2].size_line,
			&t[2].endian);
	t[3].data = mlx_get_data_addr(t[3].img, &t[3].bpp, &t[3].size_line,
			&t[3].endian);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_textures_2_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:52:07 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/11 02:56:15 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	norm_2(t_data *game, int j)
{
	while (j < 5)
	{
		mlx_destroy_image(game->mlx_ptr, game->textures[j].img);
		j++;
	}
}

void	no_image_2(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		if (game->sprite[i].img == NULL)
		{
			j = 0;
			while (j < 8)
			{
				if (j != i)
					mlx_destroy_image(game->mlx_ptr, game->sprite[j].img);
				j++;
			}
			norm_2(game, 0);
			mlx_destroy_window(game->mlx_ptr, game->mlx_win);
			mlx_destroy_display(game->mlx_ptr);
			free(game->mlx_ptr);
			error_msg_2("Problem in textures", game);
		}
		i++;
	}
}

void	norm(t_texture *t)
{
	t[0].data = mlx_get_data_addr(t[0].img, &t[0].bpp, &t[0].size_line,
			&t[0].endian);
	t[1].data = mlx_get_data_addr(t[1].img, &t[1].bpp, &t[1].size_line,
			&t[1].endian);
	t[2].data = mlx_get_data_addr(t[2].img, &t[2].bpp, &t[2].size_line,
			&t[2].endian);
	t[3].data = mlx_get_data_addr(t[3].img, &t[3].bpp, &t[3].size_line,
			&t[3].endian);
	t[4].data = mlx_get_data_addr(t[4].img, &t[4].bpp, &t[4].size_line,
			&t[4].endian);
	t[5].data = mlx_get_data_addr(t[5].img, &t[5].bpp, &t[5].size_line,
			&t[5].endian);
	t[6].data = mlx_get_data_addr(t[6].img, &t[6].bpp, &t[6].size_line,
			&t[6].endian);
	t[7].data = mlx_get_data_addr(t[7].img, &t[7].bpp, &t[7].size_line,
			&t[7].endian);
}

void	sprite_textures(t_data *game)
{
	t_texture	*t;

	t = game->sprite;
	t[0].img = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/img1.xpm",
			&t[0].width, &t[0].height);
	t[1].img = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/img2.xpm",
			&t[1].width, &t[1].height);
	t[2].img = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/img3.xpm",
			&t[2].width, &t[2].height);
	t[3].img = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/img4.xpm",
			&t[3].width, &t[3].height);
	t[4].img = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/img5.xpm",
			&t[4].width, &t[4].height);
	t[5].img = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/img6.xpm",
			&t[5].width, &t[5].height);
	t[6].img = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/img7.xpm",
			&t[6].width, &t[6].height);
	t[7].img = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/img8.xpm",
			&t[7].width, &t[7].height);
	no_image_2(game);
	norm(t);
}

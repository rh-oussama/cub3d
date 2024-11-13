/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parsing_textures_2_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:52:07 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/13 18:40:36 by alamaoui         ###   ########.fr       */
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

void	no_image_2(t_data *game, int nbr)
{
	int	i;
	int	j;

	i = 0;
	while (i < nbr)
	{
		if (game->first[i].img == NULL)
		{
			j = 0;
			while (j < nbr)
			{
				if (j != i)
					mlx_destroy_image(game->mlx_ptr, game->first[j].img);
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

void	norm(t_texture *t, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		t[i].data = mlx_get_data_addr(t[i].img, &t[i].bpp, &t[i].size_line,
				&t[i].endian);
		i++;
	}
}

void	sprite_textures(t_data *game)
{
	t_texture	*t;
	char		*name;
	char		*nbr;
	int			i;

	t = game->first;
	i = 0;
	while (i < 58)
	{
		name = NULL;
		nbr = ft_itoa(i + 1);
		name = ft_strjoin(name, "./textures/first/n");
		name = ft_strjoin(name, nbr);
		name = ft_strjoin(name, ".xpm");
		t[i].img = mlx_xpm_file_to_image(game->mlx_ptr, name, &t[i].width,
				&t[i].height);
		free(nbr);
		free(name);
		i++;
	}
	norm(t, 58);
	t = game->second;
	i = 0;
	while (i < 101)
	{
		name = NULL;
		nbr = ft_itoa(i + 1);
		name = ft_strjoin(name, "./textures/second/j");
		name = ft_strjoin(name, nbr);
		name = ft_strjoin(name, ".xpm");
		t[i].img = mlx_xpm_file_to_image(game->mlx_ptr, name, &t[i].width,
				&t[i].height);
		free(nbr);
		free(name);
		i++;
	}
	norm(t, 101);
	t = game->third;
	i = 0;
	while (i < 14)
	{
		name = NULL;
		nbr = ft_itoa(i + 1);
		name = ft_strjoin(name, "./textures/third/s");
		name = ft_strjoin(name, nbr);
		name = ft_strjoin(name, ".xpm");
		t[i].img = mlx_xpm_file_to_image(game->mlx_ptr, name, &t[i].width,
				&t[i].height);
		free(nbr);
		free(name);
		i++;
	}
	norm(t, 14);
	t = game->fourth;
	i = 0;
	while (i < 122)
	{
		name = NULL;
		nbr = ft_itoa(i + 1);
		name = ft_strjoin(name, "./textures/fourth/w");
		name = ft_strjoin(name, nbr);
		name = ft_strjoin(name, ".xpm");
		t[i].img = mlx_xpm_file_to_image(game->mlx_ptr, name, &t[i].width,
				&t[i].height);
		free(nbr);
		free(name);
		i++;
	}
	norm(t, 122);
}

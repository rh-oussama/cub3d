#include "cub3d.h"

void	textures_check(t_data *game)
{
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx_ptr, game->no_texture, &game->textures[0].width, &game->textures[0].height);
	if (game->textures[0].img == NULL)
		error_msg("No texture found");
	game->textures[0].data = mlx_get_data_addr(game->textures[0].img, &game->textures[0].bpp, &game->textures[0].size_line, &game->textures[0].endian);
	// game->textures[1].img = mlx_xpm_file_to_image(game->mlx_ptr, game->ea_texture, &game->textures[1].width, &game->textures[1].height);
	// if (game->textures[1].img == NULL)
	// 	error_msg("No texture found");
	// game->textures[1].data = mlx_get_data_addr(game->textures[1].img, &game->textures[1].bpp, &game->textures[1].size_line, &game->textures[1].endian);
	// game->textures[2].img = mlx_xpm_file_to_image(game->mlx_ptr, game->so_texture, &game->textures[2].width, &game->textures[2].height);
	// if (game->textures[2].img == NULL)
	// 	error_msg("No texture found");
	// game->textures[2].data = mlx_get_data_addr(game->textures[2].img, &game->textures[2].bpp, &game->textures[2].size_line, &game->textures[2].endian);
	// game->textures[3].img = mlx_xpm_file_to_image(game->mlx_ptr, game->we_texture, &game->textures[3].width, &game->textures[3].height);
	// if (game->textures[3].img == NULL)
	// 	error_msg("No texture found");
	// game->textures[3].data = mlx_get_data_addr(game->textures[3].img, &game->textures[3].bpp, &game->textures[3].size_line, &game->textures[3].endian);
}

char	*copy(char *s1)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(ft_strlen(s1) + 1);
	if (!res)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}


void	get_textures(t_data *game)
{
	int i = 0;
	char *no = NULL;
	// char *so = NULL;
	// char *we = NULL;
	// char *ea = NULL;
	while (game->no_texture[i])
	{
		if (game->no_texture[i] == 'N')
		{
			i++;
			if (game->no_texture[i] == 'O')
			{
				i++;
				while (game->no_texture[i])
				{
					if (game->no_texture[i] != ' ')
					{
						no = copy(&game->no_texture[i]);
						break ;
					}
					i++;
				}
				break;
			}
			else
				error_msg("Invalid configuration");
		}
	}
	game->no_texture = no;
	// i = 0;
	// while (game->so_texture[i])
	// {
	// 	if (game->so_texture[i] == 'S')
	// 	{
	// 		i++;
	// 		if (game->no_texture[i] == 'O')
	// 		{
	// 			i++;
	// 			while (game->so_texture[i])
	// 			{
	// 				if (game->so_texture[i] != ' ')
	// 				{
	// 					so = ft_strdup(&game->so_texture[i]);
	// 					break ;
	// 				}
	// 				i++;
	// 			}
	// 			break;
	// 		}
	// 		else
	// 			error_msg("Invalid configuration");
	// 	}
	// }
	// game->so_texture = so;
	// i = 0;
	// while (game->we_texture[i])
	// {
	// 	if (game->we_texture[i] == 'W')
	// 	{
	// 		i++;
	// 		if (game->we_texture[i] == 'E')
	// 		{
	// 			i++;
	// 			while (game->we_texture[i])
	// 			{
	// 				if (game->we_texture[i] != ' ')
	// 				{
	// 					we = ft_strdup(&game->we_texture[i]);
	// 					break ;
	// 				}
	// 				i++;
	// 			}
	// 			break;
	// 		}
	// 		else
	// 			error_msg("Invalid configuration");
	// 	}
	// }
	// game->we_texture = we;
	// i = 0;
	// while (game->ea_texture[i])
	// {
	// 	if (game->ea_texture[i] == 'E')
	// 	{
	// 		i++;
	// 		if (game->ea_texture[i] == 'O')
	// 		{
	// 			i++;
	// 			while (game->ea_texture[i])
	// 			{
	// 				if (game->ea_texture[i] != ' ')
	// 				{
	// 					ea = ft_strdup(&game->ea_texture[i]);
	// 					break ;
	// 				}
	// 				i++;
	// 			}
	// 			break;
	// 		}
	// 		else
	// 			error_msg("Invalid configuration");
	// 	}
	// }
	// game->ea_texture = ea;
}
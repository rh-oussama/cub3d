/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamaoui <alamaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:17:11 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/09 18:17:16 by alamaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_ceiling(t_data *game)
{
	int	i;

	i = 0;
	while (game->ceiling_parse[i] != NULL)
	{
		free(game->ceiling_parse[i]);
		i++;
	}
	free(game->ceiling_parse);
}

void	free_floor(t_data *game)
{
	int	i;

	i = 0;
	while (game->floor_parse[i] != NULL)
	{
		free(game->floor_parse[i]);
		i++;
	}
	free(game->floor_parse);
}

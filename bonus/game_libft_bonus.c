/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_libft_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaddao <orhaddao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:05:40 by alamaoui          #+#    #+#             */
/*   Updated: 2024/11/16 07:32:20 by orhaddao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_isalpha_num(int i)
{
	return ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z') || ('0' <= i
			&& i <= '9'));
}

int	ft_is_num(int i)
{
	return ('0' <= i && i <= '9');
}

char	*ft_strrchr(char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

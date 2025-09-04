/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:16:26 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/04 09:48:11 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_color(t_game *game, int i, char **rgb)
{
	if (i == 5)
	{
		game->parsing.f_color.a = 255;
		game->parsing.f_color.r = ft_atoi(rgb[0]);
		game->parsing.f_color.g = ft_atoi(rgb[1]);
		game->parsing.f_color.b = ft_atoi(rgb[2]);
	}
	else
	{
		game->parsing.c_color.a = 255;
		game->parsing.c_color.r = ft_atoi(rgb[0]);
		game->parsing.c_color.g = ft_atoi(rgb[1]);
		game->parsing.c_color.b = ft_atoi(rgb[2]);
	}
}

int	parse_color(t_game *game, int i, int k, char **identifiers)
{
	char	*line;
	char	**rgb;
	int		j;

	line = game->parsing.file_content[i];
	game->parsing.colors[k] = game->parsing.file_content[i];
	if (ft_strncmp(line, identifiers[i - 5], 2))
		return (0);
	line += (sizeof(char) * 2);
	rgb = ft_split(line, ',');
	if (!rgb)
		return (0);
	j = 0;
	while (rgb[j])
	{
		if (ft_atoi(rgb[j]) < 0 || ft_atoi(rgb[j]) > 255)
		{
			free_map(rgb);
			return (0);
		}
		j++;
	}
	assign_color(game, i, rgb);
	free_map(rgb);
	return (1);
}

int	check_colors(t_game *game)
{
	int		i;
	int		k;
	char	*identifiers[2];

	i = 5;
	k = 0;
	identifiers[0] = "F ";
	identifiers[1] = "C ";
	game->parsing.colors = (char **)malloc(sizeof(char *) * 3);
	if (!game->parsing.colors)
		return (0);
	while (i < 7)
	{
		if (!parse_color(game, i, k, identifiers))
			return (0);
		i++;
		k++;
	}
	game->parsing.colors[k] = NULL;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:16:26 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/27 02:05:04 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_color(t_game *game, int i, char **rgb)
{
	if (i == 5)
	{
		game->parsing.f_color.channels.a = 255;
		game->parsing.f_color.channels.r = ft_atoi(rgb[0]);
		game->parsing.f_color.channels.g = ft_atoi(rgb[1]);
		game->parsing.f_color.channels.b = ft_atoi(rgb[2]);
	}
	else if (i == 6)
	{
		game->parsing.c_color.channels.a = 255;
		game->parsing.c_color.channels.r = ft_atoi(rgb[0]);
		game->parsing.c_color.channels.g = ft_atoi(rgb[1]);
		game->parsing.c_color.channels.b = ft_atoi(rgb[2]);
	}
	else if (i == 7)
	{
		game->parsing.fog_color.channels.a = 0;
		game->parsing.fog_color.channels.r = ft_atoi(rgb[0]);
		game->parsing.fog_color.channels.g = ft_atoi(rgb[1]);
		game->parsing.fog_color.channels.b = ft_atoi(rgb[2]);
		game->parsing.fog_intensity = ft_atoi(rgb[3]);
	}
}

int	parse_color(t_game *game, int i, int k, char **identifiers)
{
	char	*line;
	char	**rgb;
	int		j;

	line = game->parsing.file_content[i];
	game->parsing.colors[k] = game->parsing.file_content[i];
	if (ft_strncmp(line, identifiers[k], 2))
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
			free_chartab(rgb);
			return (0);
		}
		j++;
	}
	assign_color(game, i, rgb);
	free_chartab(rgb);
	return (1);
}

int	check_colors(t_game *game)
{
	int		i;
	int		k;
	char	*identifiers[3];

	i = 5;
	k = 0;
	identifiers[0] = "F ";
	identifiers[1] = "C ";
	identifiers[2] = "A ";
	game->parsing.colors = (char **)malloc(sizeof(char *) * 4);
	if (!game->parsing.colors)
		return (0);
	while (i <= 7)
	{
		if (!parse_color(game, i, k, identifiers))
			return (0);
		i++;
		k++;
	}
	game->parsing.colors[k] = NULL;
	return (1);
}

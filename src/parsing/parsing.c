/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:03:39 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/17 14:54:33 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_path(t_game *game, int i, char **identifiers)
{
	char	*line;
	int		fd;

	line = game->file_content[i];
	game->paths[i] = game->file_content[i];
	game->paths[i] += sizeof(char) * 3;
	if (ft_strncmp(line, identifiers[i], 3))
		return (0);
	line += (sizeof(char) * 3);
	if (line)
		line[ft_strlen(line) - 1] = '\0';
	else
		return (0);
	fd = open(line, O_RDONLY);
	if (!fd || fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_paths(t_game *game)
{
	int		i;
	char	*identifiers[4];

	i = 0;
	identifiers[0] = "NO ";
	identifiers[1] = "SO ";
	identifiers[2] = "WE ";
	identifiers[3] = "EA ";
	game->paths = (char **)malloc(sizeof(char *) * 5);
	if (!game->paths)
		return (0);
	while (i < 4)
	{
		if (!assign_path(game, i, identifiers))
			return (0);
		i++;
	}
	game->paths[i] = NULL;
	return (1);
}

void	assign_color(t_game *game, int i, char **rgb)
{
	if (i == 5)
	{
		game->f_color.a = 255;
		game->f_color.r = ft_atoi(rgb[0]);
		game->f_color.g = ft_atoi(rgb[1]);
		game->f_color.b = ft_atoi(rgb[2]);
	}
	else
	{
		game->c_color.a = 255;
		game->c_color.r = ft_atoi(rgb[0]);
		game->c_color.g = ft_atoi(rgb[1]);
		game->c_color.b = ft_atoi(rgb[2]);
	}
}

int	parse_color(t_game *game, int i, int k, char **identifiers)
{
	char	*line;
	char	**rgb;
	int		j;

	line = game->file_content[i];
	game->colors[k] = game->file_content[i];
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
	char	*line;
	int		i;
	int		k;
	char	*identifiers[2];

	i = 5;
	k = 0;
	identifiers[0] = "F ";
	identifiers[1] = "C ";
	game->colors = (char **)malloc(sizeof(char *) * 3);
	if (!game->colors)
		return (0);
	while (i < 7)
	{
		if (!parse_color(game, i, k, identifiers))
			return (0);
		i++;
		k++;
	}
	game->colors[k] = NULL;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:03:39 by halnuma           #+#    #+#             */
/*   Updated: 2025/05/30 11:03:40 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_tile_validity(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'E' && \
		c != 'S' && c != 'W' && c != ' ' && c != '\n')
		return (0);
	return (1);
}


int	check_borders(char *line, int row, int line_nb)
{
	int		i;
	int		j;
	
	i = 0;
	while (line[i])
	{
		if (row == 8 || row == line_nb - 1)
		{
			if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			return (0);
		}
		else
		{
			j = 0;
			while (line[j] == ' ')
				j++;
			if (line[j] != '1')
				return (0);
			while (line[j] != '\n')
				j++;
			if (line[j - 1] != '1')
				return (0);
		}
		i++;
	}
	return (1);	
}

int	check_tiles_borders(char **map, int line_nb)
{
	int	i;
	int	j;

	i = 8;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!check_borders(map[i], i, line_nb))
				return (0);
			if (!check_tile_validity(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_paths(char **map)
{
	char	*line;
	// t_png	png;
	int		i;
	char	*identifiers[4];

	i = 0;
	identifiers[0] = "NO ";
	identifiers[1] = "SO ";
	identifiers[2] = "WE ";
	identifiers[3] = "EA ";
	while (i < 4)
	{
		line = map[i];
		if (ft_strncmp(line, identifiers[i], 3))
			return (0);
		line += (sizeof(char) * 3);
		// png = png_open(line);
		// if (!png || png == -1)
		// 	return (0);
		// png_close(png);
		i++;
	}
	return (1);
}

int	check_colors(char **map)
{
	char	*line;
	int		i;
	int		j;
	char	*identifiers[2];
	char	**rgb;

	i = 5;
	identifiers[0] = "F ";
	identifiers[1] = "C ";
	while (i < 7)
	{
		line = map[i];
		if (ft_strncmp(line, identifiers[i - 5], 2))
			return (0);
		line += (sizeof(char) * 2);
		rgb = ft_split(line, ',');
		j = 0;
		while (rgb[j])
		{
			if (ft_atoi(rgb[j]) < 0 || ft_atoi(rgb[j]) > 255)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:03:39 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/11 10:57:42 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_tiles_and_borders(t_game *game)
{
	int	i;
	int	j;
	int	k;
	int	player;
	int	width;

	i = 8;
	j = 0;
	k = 0;
	player = 0;
	game->width = 0;
	game->map = (char **)malloc(sizeof(char *) * ((game->height -7) + 1));
	game->height -= 7;
	if (!game->map)
		return (0);
	while (game->file_content[i])
	{
		j = 0;
		game->map[k] = game->file_content[i];
		width = ft_strlen(game->file_content[i]);
		if (width > game->width)
			game->width = width;
		while (game->file_content[i][j])
		{
			if (player_tile(game->file_content[i][j]))
			{
				if (player)
					return (0);
				game->player.position.x = (double)j + 0.5;
				game->player.position.y = (double)(i - 8) + 0.5;
				if (game->file_content[i][j] == 'N')
					game->player.rad_direction = M_PI / 2;
				else if (game->file_content[i][j] == 'S')
					game->player.rad_direction = 3 * M_PI / 2;
				else if (game->file_content[i][j] == 'E')
					game->player.rad_direction = M_PI;
				else if (game->file_content[i][j] == 'W')
					game->player.rad_direction = 0;
				rad_to_vect(&game->player.direction, game->player.rad_direction);
				player = 1;
			}
			if (!check_tile_validity(game->file_content[i][j]))
				return (0);
			if (center_tile(game->file_content[i][j]) && \
			!borders_around(game->file_content, i, j))
				return (0);
			j++;
		}
		i++;
		k++;
	}
	game->map[k] = NULL;
	if (!player)
		return (0);
	return (1);
}

int	check_paths(t_game *game)
{
	char	*line;
	int		fd;
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
		line = game->file_content[i];
		game->paths[i] = game->file_content[i];
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
		i++;
	}
	game->paths[i] = NULL;
	return (1);
}

int	check_colors(t_game *game)
{
	char	*line;
	int		i;
	int		j;
	int		k;
	char	*identifiers[2];
	char	**rgb;

	i = 5;
	k = 0;
	identifiers[0] = "F ";
	identifiers[1] = "C ";
	game->colors = (char **)malloc(sizeof(char *) * 3);
	if (!game->colors)
		return (0);
	while (i < 7)
	{
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
		free_map(rgb);
		i++;
		k++;
	}
	game->colors[k] = NULL;
	return (1);
}

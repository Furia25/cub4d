/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:13:59 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/02 10:29:22 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	determine_line_nb(char *map_file)
{
	int		line_nb;
	int		fd;
	char	*line;

	line_nb = 0;
	fd = open(map_file, O_RDONLY);
	if (!fd)
	{
		ft_putstr_fd("Map error", 2);
		return (0);
	}
	line = get_next_line(fd).line;
	if (line)
		line_nb++;
	while (line)
	{
		free(line);
		line = get_next_line(fd).line;
		if (line)
			line_nb++;
	}
	close(fd);
	return (line_nb);
}

char	**read_map(char *map_file, t_game *game)
{
	int		fd;
	int		i;

	fd = open(map_file, O_RDONLY);
	if (!fd || fd == -1)
	{
		ft_putstr_fd("Error while openning the map", 2);
		exit (EXIT_FAILURE);
	}
	game->height = determine_line_nb(map_file);
	game->file_content = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!(game->file_content))
		return (NULL);
	game->file_content[0] = get_next_line(fd).line;
	i = 0;
	while (++i < game->height)
	{
		game->file_content[i] = get_next_line(fd).line;
		if (!game->file_content[i])
			return (NULL);
	}
	game->file_content[i] = NULL;
	close(fd);
	return (game->file_content);
}

int	check_map_validity(t_game *game)
{
	if (!check_paths(game))
		return (0);
	if (!check_colors(game))
		return (0);
	if (!check_tiles_borders(game))
		return (0);
	return (1);
}

void	check_map_errors(t_game *game, char *map_file)
{
	if (!read_map(map_file, game))
	{
		ft_putstr_fd("Error: Malloc failed", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_map_validity(game))
	{
		free_map(game->file_content);
		ft_putstr_fd("Error: The map is not valid", 2);
		exit(EXIT_FAILURE);
	}
}

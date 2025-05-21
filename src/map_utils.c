/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:13:59 by halnuma           #+#    #+#             */
/*   Updated: 2025/05/21 11:29:29 by halnuma          ###   ########.fr       */
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
	line = get_next_line(fd);
	if (line)
		line_nb++;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
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
	game->map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!(game->map))
		return (NULL);
	game->map[0] = get_next_line(fd);
	i = 0;
	while (++i < game->height)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i])
			return (NULL);
	}
	game->map[i] = NULL;
	close(fd);
	return (game->map);
}

int	check_tile_validity(char c)
{
	if (c != '1' && c != '0' && c != 'N' && \
		c != 'E' && c != 'S' && c != 'W' && c != '\n')
		return (0);
	return (1);
}

int	check_tiles(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!check_tile_validity(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_validity(char **map)
{
	if (!check_tiles(map))
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
	if (!check_map_validity(game->map))
	{
		free_map(game->map);
		ft_putstr_fd("Error: The map is not valid", 2);
		exit(EXIT_FAILURE);
	}
}

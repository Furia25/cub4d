/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:03:39 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/04 09:48:38 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**read_npc_text(t_game *game)
{
	int		line_nb;
	int		fd;
	int		i;

	fd = open("assets/text/npc.txt", O_RDONLY);
	if (!fd || fd == -1)
	{
		ft_putstr_fd("Error while openning the npc text file", 2);
		exit (EXIT_FAILURE);
	}
	line_nb = determine_line_nb("assets/text/npc.txt");
	game->parsing.npc_text = (char **)malloc(sizeof(char *) * (line_nb + 1));
	if (!(game->parsing.npc_text))
		return (NULL);
	game->parsing.npc_text[0] = get_next_line(fd).line;
	i = 0;
	while (++i < line_nb)
	{
		game->parsing.npc_text[i] = get_next_line(fd).line;
		if (!game->parsing.npc_text[i])
			return (NULL);
	}
	game->parsing.npc_text[i] = NULL;
	close(fd);
	return (game->parsing.npc_text);
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
	game->parsing.map_height = determine_line_nb(map_file);
	game->parsing.file_content = (char **)malloc(sizeof(char *) * (game->parsing.map_height + 1));
	if (!(game->parsing.file_content))
		return (NULL);
	game->parsing.file_content[0] = get_next_line(fd).line;
	i = 0;
	while (++i < game->parsing.map_height)
	{
		game->parsing.file_content[i] = get_next_line(fd).line;
		if (!game->parsing.file_content[i])
			return (NULL);
	}
	game->parsing.file_content[i] = NULL;
	close(fd);
	return (game->parsing.file_content);
}

int	check_map_validity(t_game *game)
{
	if (!check_paths(game))
		return (0);
	if (!check_colors(game))
		return (0);
	if (!check_tiles_and_borders(game))
		return (0);
	return (1);
}

void	parsing(t_game *game, char *map_file)
{
	if (!read_npc_text(game))
	{
		free_map(game->parsing.file_content);
		ft_putstr_fd("Error: Reading npc text file failed", 2);
		exit(EXIT_FAILURE);
	}
	if (!read_map(map_file, game))
	{
		ft_putstr_fd("Error: Malloc failed", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_map_validity(game))
	{
		free_map(game->parsing.file_content);
		ft_putstr_fd("Error: The map is not valid", 2);
		exit(EXIT_FAILURE);
	}
}

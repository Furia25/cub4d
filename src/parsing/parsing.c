/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 23:58:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/28 18:19:35 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	read_file(t_parsing *parsing, t_game *game);

void	parsing(char *file_name, t_game *game)
{
	t_parsing	*parsing;

	parsing = &game->parsing;
	parsing->file_fd = open(file_name, O_RDONLY);
	if (parsing->file_fd == -1)
		throw_error(game, ERROR_PARSING_IO);
	parsing->file_length = file_length(file_name);
	if (parsing->file_length == -1)
		throw_error(game, ERROR_ALLOC);
	else if (parsing->file_length == -2)
		throw_error(game, ERROR_PARSING_IO);
	else if (parsing->file_length == 0)
		throw_error(game, ERROR_PARSING_VALIDITY);
	read_file(parsing, game);
	close(parsing->file_fd);
	parsing->file_fd = -1;
	interpret_map_from_file(parsing, game);
	if (!parsing->has_ceil || !parsing->has_floor)
		throw_error(game, ERROR_PARSING_MISSING_COLOR);
	if (!parsing->textures_paths[0] || !parsing->textures_paths[1]
		|| !parsing->textures_paths[2] || !parsing->textures_paths[3])
		throw_error(game, ERROR_PARSING_MISSING_PATHS);
	game->tilemap = tilemap_from_tab(game->parsing.map,
		game->parsing.map_width, game->parsing.map_height, 1);
	printf(INFO_PREFIX PARSING_MAP_MESSAGE, parsing->map_width, parsing->map_height);
}

static inline void	read_file(t_parsing *parsing, t_game *game)
{
	t_gnl_result	line;
	int				i;

	parsing->file_content = ft_calloc(parsing->file_length + 1, sizeof(char *));
	if (!parsing->file_content)
		throw_error(game, ERROR_ALLOC);
	i = 0;
	line = get_next_line(parsing->file_fd);
	while (!line.error && i < parsing->file_length)
	{
		parsing->file_content[i++] = line.line;
		if (line.ended)
		{
			parsing->file_content[i] = NULL;
			return ;
		}
		line = get_next_line(parsing->file_fd);
	}
	free(line.line);
	throw_error(game, ERROR_PARSING_IO);
}

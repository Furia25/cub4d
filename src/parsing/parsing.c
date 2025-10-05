/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 23:58:56 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 01:31:25 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

static inline void	read_mapfile(t_parsing *parsing, t_game *game);
static inline void	parsing_end(t_parsing *parsing, t_game *game);
static inline void	parsing_check_mandatory(t_parsing *parsing, t_game *game);

void	parsing(char *file_name, t_game *game)
{
	t_parsing	*parsing;

	parsing = &game->parsing;
	parsing->file_fd = open(file_name, O_RDONLY);
	if (parsing->file_fd == -1)
		throw_error(ERROR_PARSING_IO, game);
	parsing->file_length = file_length(file_name);
	if (parsing->file_length == -1)
		throw_error(ERROR_ALLOC, game);
	else if (parsing->file_length == -2)
		throw_error(ERROR_PARSING_IO, game);
	else if (parsing->file_length == 0)
		throw_error(ERROR_PARSING_VALIDITY, game);
	read_mapfile(parsing, game);
	close(parsing->file_fd);
	parsing->file_fd = -1;
	parsing->line_num = 0;
	argument_error_queue_init(game);
	interpret_map_from_file(parsing, game);
	parsing_end(parsing, game);
}

static inline void	parsing_end(t_parsing *parsing, t_game *game)
{
	parsing_check_mandatory(parsing, game);
	game->tilemap = tilemap_from_tab(game->parsing.map,
			game->parsing.map_width, game->parsing.map_height, 1);
	map_check_borders(parsing, game);
	free_tab((void **)parsing->file_content);
	parsing->file_content = NULL;
	argument_error_queue_clean();
	printf(INFO_PREFIX PARSING_MAP_MESSAGE,
		parsing->map_width, parsing->map_height);
}

static inline void	parsing_check_mandatory(t_parsing *parsing, t_game *game)
{
	if (!parsing->has_player)
		throw_error(ERROR_PARSING_NOPLAYER, game);
	if (!parsing->has_ceil || !parsing->has_floor)
		throw_error(ERROR_PARSING_MISSING_COLOR, game);
	if (!parsing->textures_paths[0]
		|| !parsing->textures_paths[1]
		|| !parsing->textures_paths[2]
		|| !parsing->textures_paths[3])
		throw_error(ERROR_PARSING_MISSING_PATHS, game);
	parsing->ceil_color.channels.a = 255;
	parsing->floor_color.channels.a = 255;
}

static inline void	read_mapfile(t_parsing *parsing, t_game *game)
{
	t_gnl_result	line;
	int				i;

	parsing->file_content = ft_calloc(parsing->file_length + 1, sizeof(char *));
	if (!parsing->file_content)
		throw_error(ERROR_ALLOC, game);
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
		else
			line.line[ft_strlen(line.line) - 1] = '\0';
		line = get_next_line(parsing->file_fd);
	}
	free(line.line);
	throw_error(ERROR_PARSING_IO, game);
}

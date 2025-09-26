/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:03:39 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/26 17:22:43 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_map(t_parsing *parsing, t_game *game)
{
	t_gnl_result	line;
	int				i;

	parsing->file_content = malloc(sizeof(char *) * (parsing->file_length + 1));
	if (!parsing->file_content)
		throw_error(game, ERROR_ALLOC);
	i = 0;
	line = get_next_line(parsing->file_fd);
	while (!line.error)
	{
		parsing->file_content[i++] = line.line;
		if (line.ended)
		{
			parsing->file_content[i] = NULL;
			parsing->map_height = i;
			return ;
		}
		line = get_next_line(parsing->file_fd);
	}
	free(line.line);
	throw_error(game, ERROR_PARSING_IO);
}

void	parsing(t_game *game, char *map_file)
{
	game->parsing.file_fd = open(map_file, O_RDONLY);
	if (game->parsing.file_fd == -1)
		throw_error(game, ERROR_PARSING_IO);
	game->parsing.file_length = file_length(map_file);
	if (game->parsing.file_length < 0)
		throw_error(game, ERROR_PARSING_IO);
	if (game->parsing.file_length == 0)
		throw_error(game, ERROR_PARSING_VALIDITY);
	read_map(&game->parsing, game);
	if (!check_paths(game) || !check_colors(game)
		|| !check_tiles_and_borders(&game->parsing, game))
		throw_error(game, ERROR_PARSING_VALIDITY);
}

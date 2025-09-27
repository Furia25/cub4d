/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:02:07 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/27 02:24:41 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline int	get_last_non_empty_line(t_parsing *parsing);
static inline void	parse_map_from_file(t_parsing *parsing, t_game *game);
static inline void	parse_map_line(char *line, int y,
						t_parsing *parsing, t_game *game);
static inline bool	check_tile_border(int x, int y,
						char **map, t_parsing *parsing);

void	try_parse_map(int index, t_parsing *parsing, t_game *game)
{
	parsing->map_start = index;
	parsing->map_end = get_last_non_empty_line(parsing);
	parsing->map_height = parsing->map_end - parsing->map_start;
	if (parsing->map_height <= 0)
		throw_error(game, ERROR_PARSING_VALIDITY);
	parsing->map = ft_calloc(parsing->map_height + 1, sizeof(char *));
	if (!parsing->map)
		throw_error(game, ERROR_PARSING_ALLOC);
	parsing->map_width = 0;
	parsing->has_player = false;
	parse_map_from_file(parsing, game);
}

static inline int	get_last_non_empty_line(t_parsing *parsing)
{
	int	index;

	index = parsing->file_length - 1;
	while (index >= 0 && is_str_empty(parsing->file_content[index]))
		index--;
	return (index);
}

static inline void	parse_map_from_file(t_parsing *parsing, t_game *game)
{
	int		y;
	int		map_y;
	char	*line;
	size_t	width;

	y = parsing->map_start;
	map_y = 0;
	while (y <= parsing->map_end && parsing->file_content[y])
	{
		line = parsing->file_content[y];
		parsing->map[map_y++] = line;
		width = ft_strlen(line) - 1;
		if (parsing->map_width < width)
			parsing->map_width = width;
		if (width > 0)
			parse_map_line(line, y, parsing, game);
		else
			throw_error(game, ERROR_PARSING_NL_MAP);
		y++;
	}
}

static inline void	parse_map_line(char *line, int y,
						t_parsing *parsing, t_game *game)
{
	int	x;

	x = 0;
	while (x < parsing->map_width && line[x])
	{
		if (!is_symbol_valid(line[x]))
			throw_error(game, ERROR_PARSING_SYMBOL);
		if (line[x] == '\n')
			line[x] == ' ';
		if (is_symbol_player(line[x]))
			map_set_player_pos(x, y, parsing, game);
		if (is_symbol_central(line[x])
			&& !check_tile_border(x, y, parsing->map, parsing))
			throw_error(game, ERROR_PARSING_UNCLOSED);
		x++;
	}
}

static inline bool	check_tile_border(int x, int y,
						char **map, t_parsing *parsing)
{
	int		relative_y;

	relative_y = y - parsing->map_start - 1;
	printf("%c : %d\n", map[y][x], relative_y);
	/*if (relative_y <= parsing->map_height && !is_valid_tile(map[y + 1][x]))
		return (0);*/
	return (1);
}

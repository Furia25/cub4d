/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:02:07 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 19:04:59 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	parse_map_from_file(t_parsing *parsing, t_game *game);
static inline int		map_get_width(t_parsing *parsing);
static inline void	parse_map_line(char *line, int y,
						t_parsing *parsing, t_game *game);

void	try_parse_map(int index, t_parsing *parsing, t_game *game)
{
	int	end_nls;

	parsing->map_start = index;
	end_nls = parsing->file_length - 1;
	while (end_nls >= 0 && is_str_empty(parsing->file_content[end_nls]))
		end_nls--;
	parsing->map_end = end_nls;
	parsing->map_height = parsing->map_end - parsing->map_start + 1;
	if (parsing->map_height <= 0)
		throw_error(ERROR_PARSING_VALIDITY, game);
	parsing->map = ft_calloc(parsing->map_height + 3, sizeof(char *));
	if (!parsing->map)
		throw_error(ERROR_PARSING_ALLOC, game);
	parsing->map_width = map_get_width(parsing);
	if (parsing->map_width <= 0)
		throw_error(ERROR_PARSING_VALIDITY, game);
	parsing->has_player = false;
	parse_map_from_file(parsing, game);
}

static inline int	map_get_width(t_parsing *parsing)
{
	int	index;
	int	maxi;
	int	temp;

	index = parsing->map_start;
	maxi = 0;
	while (index <= parsing->map_end && parsing->file_content[index])
	{
		temp = ft_strlen(parsing->file_content[index]);
		if (temp > maxi)
			maxi = temp;
		index++;
	}
	return (maxi);
}

static inline void	parse_map_from_file(t_parsing *parsing, t_game *game)
{
	int		y;
	char	*line;
	size_t	length;

	y = parsing->map_start;
	while (y <= parsing->map_end && parsing->file_content[y])
	{
		if (parsing->file_content[y][0] == '\0')
			throw_error(ERROR_PARSING_NL_MAP, game);
		line = ft_calloc(parsing->map_width + 1, sizeof(char));
		if (!line)
			throw_error(ERROR_PARSING_ALLOC, game);
		length = ft_strlen(parsing->file_content[y]);
		if (length > (size_t)parsing->map_width)
			throw_error(ERROR_PARSING_VALIDITY, game);
		ft_memcpy(line, parsing->file_content[y], length);
		parsing->map[y - parsing->map_start] = line;
		parse_map_line(line, y - parsing->map_start, parsing, game);
		y++;
	}
}

static inline void	parse_map_line(char *line, int y,
						t_parsing *parsing, t_game *game)
{
	int		x;
	char	c;

	x = 0;
	while (x < parsing->map_width && line[x])
	{
		c = line[x];
		if (!is_symbol_valid(c))
			throw_error(ERROR_PARSING_SYMBOL, game);
		if (is_symbol_player(c))
			map_set_player_pos(x, y, parsing, game);
		x++;
	}
}

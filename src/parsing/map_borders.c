/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_borders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:21:48 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/29 19:53:48 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline bool	check_neighbour_central(int x, int y,
						t_parsing *parsing);
static inline bool	check_neighbour_valid(int x, int y, t_parsing *parsing);

void	map_check_borders(t_parsing *parsing, t_game *game)
{
	char	c;
	int		x;
	int		y;

	parsing->temp_map = chartab_dup(parsing->map, parsing->map_height);
	if (!parsing->temp_map)
		throw_error(game, ERROR_PARSING_ALLOC);
	y = 0;
	while (y < parsing->map_height)
	{
		x = 0;
		while (x < parsing->map_width)
		{
			c = parsing->temp_map[y][x];
			if (is_symbol_central(c) || c == ' ')
			{
				if ((c != ' ' || check_neighbour_central(x, y, parsing)) 
					&& !check_neighbour_valid(x, y, parsing))
					throw_error(game, ERROR_PARSING_UNCLOSED);
			}
			x++;
		}
		y++;
	}
	print_char_tab(parsing->temp_map);
	free_chartab(parsing->temp_map);
	parsing->temp_map = NULL;
}

static inline bool	check_neighbour_central(int x, int y, t_parsing *parsing)
{
	char	**map;

	map = parsing->temp_map;
	if (x > 0 && is_symbol_central(map[y][x - 1]))
		return (true);
	if (y > 0 && is_symbol_central(map[y - 1][x]))
		return (true);
	if (x < parsing->map_width && is_symbol_central(map[y][x + 1]))
		return (true);
	if (y < parsing->map_height && is_symbol_central(map[y + 1][x]))
		return (true);
	return (false);
}

static inline bool	check_neighbour_valid(int x, int y,
						t_parsing *parsing)
{
	char	**map;

	map = parsing->temp_map;
	map[y][x] = '2';
	if (x < 1 || !is_symbol_valid(map[y][x - 1]))
		return (false);
	if (y < 1 || !is_symbol_valid(map[y - 1][x]))
		return (false);
	if (x >= parsing->map_width || !is_symbol_valid(map[y][x + 1]))
		return (false);
	if (y >= parsing->map_height || !is_symbol_valid(map[y + 1][x]))
		return (false);
	return (true);
}

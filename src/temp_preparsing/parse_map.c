/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:34:48 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/27 00:14:40 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop_through_line(int i, t_parsing_content *map_content,
		t_parsing *parsing, t_game *game)
{
	int	j;

	j = 0;
	while (parsing->file_content[i][j] && j < parsing->map_width)
	{
		if (!is_valid_tile(parsing->file_content[i][j]))
		{
			printf("zizi1\n");
			return (0);
		}
		if (is_center_tile(parsing->file_content[i][j])
			&& !borders_around(parsing->file_content, i, j, parsing))
		{
			printf("zizi2\n");
			return (0);
		}
		
		if (!check_player(game, i, j, &map_content->player))
		{
			printf("zizi3\n");
			return (0);
		}
		j++;
	}
	return (1);
}

//TEMP
void	print_char_tab(char **tab, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			printf(x == width - 1 ? "%c ": "%c", tab[y][x]);
		printf("\n");
	}
}
//temp;

int	loop_through_map(t_parsing *parsing, t_parsing_content *map_content,
		t_game *game)
{
	int	i;
	int	k;
	int	width;

	i = parsing->map_start;
	k = 0;
	map_content->enemies = 0;
	map_content->npcs = 0;
	while (parsing->file_content[i] && i < parsing->map_end)
	{
		parsing->map[k++] = parsing->file_content[i];
		width = ft_strlen(parsing->file_content[i]) - 1;
		if (width > parsing->map_width)
			parsing->map_width = width;
		if (!loop_through_line(i, map_content, parsing, game))
			return (0);
		i++;
	}
	return (1);
}

/*Find height from newline*/

void	find_height(int *start, int *end, t_parsing *parsing)
{
	char	*line;
	int		i;

	i = PARSING_MAP_START;
	*end = parsing->file_length;
	while (parsing->file_content[i])
	{
		line = parsing->file_content[i];
		if (!is_str_empty(line))
			break ;
		i++;
	}
	*start = i;
	while (parsing->file_content[i])
	{
		line = parsing->file_content[i];
		if (is_str_empty(line))
			break ;
		i++;
	}
	*end = i;
}

int	check_tiles_and_borders(t_parsing *parsing, t_game *game)
{
	t_parsing_content	map_content;

	map_content.player = 0;
	game->parsing.map_width = 0;
	find_height(&parsing->map_start, &parsing->map_end, parsing);
	parsing->map_height = parsing->map_end - parsing->map_start;
	if (parsing->map_height <= 0)
		return (0);
	parsing->map = ft_calloc(parsing->map_height + 1, sizeof(char *));
	if (!parsing->map)
		return (0);
	if (!loop_through_map(parsing, &map_content, game))
		return (0);
	if (!map_content.player)
	{
		printf("%d\n", map_content.player);
		return (0);
	}
	printf(PARSING_MAP_MESSAGE, parsing->map_width, parsing->map_height);
	return (1);
}

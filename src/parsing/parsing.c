/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:03:39 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/16 14:34:40 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_pnj_text(t_game *game, t_pnj *pnj, int index)
{
	int		i;
	int		line_count;
	int		tmp_count;
	int		size;
	char	**pnj_text;

	(void)pnj;
	line_count = 0;
	i = 0;
	while (i < index)
	{
		while (game->pnj_text[line_count] && ft_strcmp(game->pnj_text[line_count], "\n"))
			line_count++;
		line_count++;
		i++;
	}
	tmp_count = line_count;
	size = 0;
	while (game->pnj_text[tmp_count] && ft_strcmp(game->pnj_text[tmp_count], "\n"))
	{
		size++;
		tmp_count++;
	}
	pnj_text = (char **)malloc(sizeof(char *) * size);
	i = 0;
	while (i < size - 1)
	{
		pnj_text[i] = ft_strdup(game->pnj_text[i + line_count + 1]);
		i++;
	}
	pnj_text[size - 1] = NULL;
	pnj->text = pnj_text;
}

int	check_tiles_and_borders(t_game *game)
{
	int	i;
	int	j;
	int	k;
	int	e;
	int	p;
	int	player;
	int	width;

	i = 8;
	j = 0;
	k = 0;
	e = 0;
	p = 0;
	player = 0;
	game->width = 0;
	game->map = (char **)malloc(sizeof(char *) * ((game->height -7) + 1));
	game->height -= 7;
	game->enemy_count = 0;
	game->pnj_count = 0;
	if (!game->map)
		return (0);
	while (game->file_content[i])
	{
		j = 0;
		game->map[k] = game->file_content[i];
		width = ft_strlen(game->file_content[i]);
		if (width > game->width)
			game->width = width;
		while (game->file_content[i][j])
		{
			if (player_tile(game->file_content[i][j]))
			{
				if (player)
					return (0);
				game->player.position.x = (double)j + 0.5;
				game->player.position.y = (double)(i - 8) + 0.5;
				if (game->file_content[i][j] == 'S')
					game->player.rad_direction = M_PI / 2;
				else if (game->file_content[i][j] == 'N')
					game->player.rad_direction = 3 * M_PI / 2;
				else if (game->file_content[i][j] == 'W')
					game->player.rad_direction = M_PI;
				else if (game->file_content[i][j] == 'E')
					game->player.rad_direction = 0;
				rad_to_vect(&game->player.direction, game->player.rad_direction);
				player = 1;
			}
			if (!check_tile_validity(game->file_content[i][j]))
				return (0);
			if (center_tile(game->file_content[i][j]) && \
			!borders_around(game->file_content, i, j))
				return (0);
			if (game->file_content[i][j] == 'M')
			{
				if (game->enemy_count >= MAX_ENEMIES)
					return (0);
				game->enemies[e].position.x = (double)j + 0.5;
				game->enemies[e].position.y = (double)(i - 8) + 0.5;
				game->enemies[e].hp = 100;
				game->enemies[e].state = SLEEPING;
				game->enemy_count++;
				e++;
			}
			if (game->file_content[i][j] == 'P')
			{
				if (game->pnj_count >= MAX_PNJ)
					return (0);
				game->pnjs[p].position.x = (double)j + 0.5;
				game->pnjs[p].position.y = (double)(i - 8) + 0.5;
				// game->pnjs[p].text = g_pnj_text[p];
				game->pnj_count++;
				assign_pnj_text(game, &game->pnjs[p], p);
				p++;
			}
			j++;
		}
		i++;
		k++;
	}
	game->map[k] = NULL;
	if (!player)
		return (0);
	return (1);
}

int	check_paths(t_game *game)
{
	char	*line;
	int		fd;
	int		i;
	char	*identifiers[4];

	i = 0;
	identifiers[0] = "NO ";
	identifiers[1] = "SO ";
	identifiers[2] = "WE ";
	identifiers[3] = "EA ";
	game->paths = (char **)malloc(sizeof(char *) * 5);
	if (!game->paths)
		return (0);
	while (i < 4)
	{
		line = game->file_content[i];
		game->paths[i] = game->file_content[i];
		game->paths[i] += sizeof(char) * 3;
		if (ft_strncmp(line, identifiers[i], 3))
			return (0);
		line += (sizeof(char) * 3);
		if (line)
			line[ft_strlen(line) - 1] = '\0';
		else
			return (0);
		fd = open(line, O_RDONLY);
		if (!fd || fd == -1)
			return (0);
		close(fd);
		i++;
	}
	game->paths[i] = NULL;
	return (1);
}

int	check_colors(t_game *game)
{
	char	*line;
	int		i;
	int		j;
	int		k;
	char	*identifiers[2];
	char	**rgb;

	i = 5;
	k = 0;
	identifiers[0] = "F ";
	identifiers[1] = "C ";
	game->colors = (char **)malloc(sizeof(char *) * 3);
	if (!game->colors)
		return (0);
	while (i < 7)
	{
		line = game->file_content[i];
		game->colors[k] = game->file_content[i];
		if (ft_strncmp(line, identifiers[i - 5], 2))
			return (0);
		line += (sizeof(char) * 2);
		rgb = ft_split(line, ',');
		if (!rgb)
			return (0);
		j = 0;
		while (rgb[j])
		{
			if (ft_atoi(rgb[j]) < 0 || ft_atoi(rgb[j]) > 255)
			{
				free_map(rgb);
				return (0);
			}
			j++;
		}
		if (i == 5)
		{
			game->f_color.a = 255;
			game->f_color.r = ft_atoi(rgb[0]);
			game->f_color.g = ft_atoi(rgb[1]);
			game->f_color.b = ft_atoi(rgb[2]);
		}
		else
		{
			game->c_color.a = 255;
			game->c_color.r = ft_atoi(rgb[0]);
			game->c_color.g = ft_atoi(rgb[1]);
			game->c_color.b = ft_atoi(rgb[2]);
		}
		free_map(rgb);
		i++;
		k++;
	}
	game->colors[k] = NULL;
	return (1);
}

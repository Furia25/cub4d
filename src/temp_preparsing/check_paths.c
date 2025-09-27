/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:16:07 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/04 09:47:56 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_path(t_game *game, int i, char **identifiers)
{
	char	*line;

	line = game->parsing.file_content[i];
	game->parsing.paths[i] = game->parsing.file_content[i];
	game->parsing.paths[i] += 3;
	if (ft_strncmp(line, identifiers[i], 3))
		return (0);
	line += 3;
	if (line)
		line[ft_strlen(line) - 1] = '\0';
	else
		return (0);
	return (1);
}

int	check_paths(t_game *game)
{
	int		i;
	char	*identifiers[4];

	i = 0;
	identifiers[0] = "NO ";
	identifiers[1] = "SO ";
	identifiers[2] = "WE ";
	identifiers[3] = "EA ";
	game->parsing.paths = (char **)malloc(sizeof(char *) * 5);
	if (!game->parsing.paths)
		return (0);
	while (i < 4)
	{
		if (!assign_path(game, i, identifiers))
			return (0);
		i++;
	}
	game->parsing.paths[i] = NULL;
	return (1);
}

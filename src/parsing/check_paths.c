/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:16:07 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/21 19:19:01 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_path(t_game *game, int i, char **identifiers)
{
	char	*line;

	line = game->file_content[i];
	game->paths[i] = game->file_content[i];
	game->paths[i] += 3;
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
	game->paths = (char **)malloc(sizeof(char *) * 5);
	if (!game->paths)
		return (0);
	while (i < 4)
	{
		if (!assign_path(game, i, identifiers))
			return (0);
		i++;
	}
	game->paths[i] = NULL;
	return (1);
}

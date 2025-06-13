/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:56:13 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/13 09:32:59 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_borders(char *line, int row, int line_nb)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (row == 8 || row == line_nb - 1)
		{
			if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
				return (0);
		}
	}
	return (1);
}

int	borders_around(char **map, int i, int j)
{
	if (!wrapping_tile(map[i + 1][j]) || !wrapping_tile(map[i - 1][j]))
		return (0);
	if (!wrapping_tile(map[i][j + 1]) || !wrapping_tile(map[i][j - 1]))
		return (0);
	return (1);
}

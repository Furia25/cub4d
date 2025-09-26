/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:56:13 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/26 18:56:03 by vdurand          ###   ########.fr       */
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

int	borders_around(char **map, int i, int j, t_parsing *parsing)
{
	printf("%c : %dx%d \n", map[i][j], j, i);
	printf("%c\n", map[1][0]);
	if (i < parsing->map_height && !is_wrapping_tile(map[i + 1][j]))
		printf("ZIZI\n");
	return (1);
}

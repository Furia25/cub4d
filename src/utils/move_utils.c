/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:09:30 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/27 16:06:41 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rad_to_vect(t_vec2 *direction, float rad)
{
	direction->x = cos(rad);
	direction->y = sin(rad);
}

void	player_add_x(float value, t_player *player)
{
	player->position.x += value;
	player->bbox.min.x += value;
	player->bbox.max.x += value;
}

void	player_add_y(float value, t_player *player)
{
	player->position.y += value;
	player->bbox.min.y += value;
	player->bbox.max.y += value;
}

void	player_add_z(float value, t_player *player)
{
	player->position.z += value;
	player->bbox.min.z += value;
	player->bbox.max.z += value;
}

int	check_player(t_game *game, int i, int j, int *player)
{
	if (is_symbol_player(game->parsing.file_content[i][j]))
	{
		if (*player)
			return (0);
		game->player.position.x = (double)j + 0.5;
		game->player.position.y = (double)(i - 8) + 0.5;
		if (game->parsing.file_content[i][j] == 'S')
			game->player.yaw_rad = M_PI / 2;
		else if (game->parsing.file_content[i][j] == 'N')
			game->player.yaw_rad = 3 * M_PI / 2;
		else if (game->parsing.file_content[i][j] == 'W')
			game->player.yaw_rad = M_PI;
		else if (game->parsing.file_content[i][j] == 'E')
			game->player.yaw_rad = 0;
		rad_to_vect(&game->player.direction, game->player.yaw_rad);
		*player = 1;
	}
	return (1);
}
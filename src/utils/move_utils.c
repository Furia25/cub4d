/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:09:30 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/24 20:35:38 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rad_to_vect(t_vec2 *direction, float rad)
{
	direction->x = cos(rad);
	direction->y = sin(rad);
}

int mouse_move(int x, int y, t_game *game)
{
	double		width;
	double		x_dif;
	static int	last_x = 0;

	(void) y;
	if (last_x == x)
		return (1);
	last_x = x;
	width = game->w_halfwidth;
	x_dif = (x - width) * MOUSE_SENS;
	game->player.rad_direction += x_dif;
	mlx_mouse_move(game->mlx, game->win, width, game->w_halfheight);
	return (1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:09:30 by halnuma           #+#    #+#             */
/*   Updated: 2025/08/16 02:43:37 by vdurand          ###   ########.fr       */
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
	double		x_dif;
	double		y_dif;
	static int	last_x = 0;
	static int	last_y = 0;

	if (last_x == x)
		return (1);
	if (last_y == y)
		return (1);
	last_x = x;
	x_dif = (x - game->w_halfwidth) * MOUSE_SENS;
	last_y = y;
	y_dif = -(y - game->w_halfheight);
	game->player.yaw_rad += x_dif;
	game->player.pitch_offset += y_dif;
	game->player.pitch_offset = clamp(game->player.pitch_offset, -600, 600);
	mlx_mouse_move(game->mlx, game->win, game->w_halfwidth, game->w_halfheight);
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

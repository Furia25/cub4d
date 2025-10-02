/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:09:30 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/02 03:22:19 by vdurand          ###   ########.fr       */
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

void	object_move(t_vec3 offset, t_vec3 *pos, t_bbox *bbox)
{
	pos->x += offset.x;
	pos->y += offset.y;
	pos->z += offset.z;
	bbox_add(offset, bbox);
}

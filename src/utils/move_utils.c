/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:09:30 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/02 04:22:59 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rad_to_vect(t_vec2 *direction, float rad)
{
	direction->x = cos(rad);
	direction->y = sin(rad);
}

void	object_set_pos(t_vec3 new_pos, t_vec3 *pos, t_bbox *bbox)
{
	t_vec3	offset;

	offset = vec3_sub(new_pos, *pos);
	bbox_add(offset, bbox);
	*pos = new_pos;
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

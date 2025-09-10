/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:27:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/10 03:22:18 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"

void	entity_free(t_entity *entity)
{
	if (entity->free_data)
		entity->free_data(entity->data);
	free(entity);
}

void	entity_init_basics(t_vec3 position, t_entity *entity)
{
	entity->free_data = free;
	entity->position = position;
	entity->spr.spr_per_line = 1;
	entity->transform.color = g_colors[C_WHITE];
	entity->transform.width = 100;
	entity->transform.height = 200;
	entity->transform.index = 0;
	entity->transform.scale = 1;
	entity->hitbox.min = (t_vec3){position.x - 0.2, position.y- 0.4, position.z};
	entity->hitbox.max = (t_vec3){position.x, position.y, position.z + 0.2};
	entity->map_color = g_colors[C_AZURE];
}

void	entity_basic_draw(t_entity *entity, t_render_context *render)
{
	t_vec3				relative;
	t_vec3				cam_pos;
	t_vec2				projected;

	
	relative = vec3_sub(bbox_get_center(entity->hitbox), render->player->position);
    cam_pos.z = relative.x * render->yaw_cos + relative.y * render->yaw_sin;
	if (cam_pos.z <= 0.01 || cam_pos.z > RENDER_DISTANCE)
		return ;
	cam_pos.x = relative.y * render->yaw_cos - relative.x * render->yaw_sin;
    cam_pos.y = relative.z;
	projected.x = (cam_pos.x / cam_pos.z) * render->focal * render->ratio;
	projected.y = (cam_pos.y / cam_pos.z) * render->focal * render->ratio;
	entity->transform.x = (projected.x + 1.0f) * render->halfw;
	entity->transform.y = (1.0f - projected.y) * render->halfh;
	entity->transform.scale = render->aspect_res * (2.f / cam_pos.z);
	entity->transform.depth = vec3_length(relative);
	draw_sprite_entity(entity->transform, entity, render);
}

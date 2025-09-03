/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:27:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/03 21:19:44 by vdurand          ###   ########.fr       */
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
	entity->spr.sprite_per_line = 1;
	entity->transform.color = g_colors[C_WHITE];
	entity->transform.width = 100;
	entity->transform.height = 200;
	entity->transform.index = 0;
	entity->transform.scale = 1;
	entity->map_color = g_colors[C_AZURE];
}

void	entity_basic_draw(t_entity *entity, t_render_context *render)
{
	t_vec3	relative;
	t_vec3	cam_pos;
	t_vec2	projected;

	relative = vec3_sub(entity->position, render->player->position);
    cam_pos.z = relative.x * render->yaw_cos + relative.y * render->yaw_sin;
	if (cam_pos.z <= 0.01)
		return ;
	cam_pos.x = relative.y * render->yaw_cos - relative.x * render->yaw_sin;
    cam_pos.y = relative.z;
	float	aspect_ratio = (float)(render->render_width) / (float)(render->render_height);
	float	f = 1.0f / tanf(render->fov * 0.5);
	projected.x = (cam_pos.x / cam_pos.z) * f * aspect_ratio;
	projected.y = (cam_pos.y / cam_pos.z) * f;
	entity->transform.x = (projected.x + 1.0f) * render->halfw;
	entity->transform.y = (1.0f - projected.y) * render->halfh;
	entity->transform.depth = cam_pos.z;
	entity->transform.scale = 0.1f / cam_pos.z;
	printf("TEST:%f\n", entity->transform.scale);
	draw_sprite_entity(entity->transform, &entity->spr, render);
}

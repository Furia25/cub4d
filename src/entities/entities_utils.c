/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:27:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/26 02:58:38 by vdurand          ###   ########.fr       */
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
	entity->transform.height = 100;
	entity->transform.index = 0;
	entity->map_color = g_colors[C_AZURE];
}

void	entity_basic_draw(t_entity *entity, t_render_context *render)
{
	t_vec3	rel;
	t_vec3	cam_pos;
	t_vec2	screen_pos;

	rel = vec3_sub(entity->position, render->player->position);
	cam_pos.z = rel.x * render->yaw_sin - rel.y * render->yaw_cos;
	if (cam_pos.z <= 0.01f)
		return ;
	cam_pos.x = rel.x * render->yaw_cos + rel.y * render->yaw_sin;
	cam_pos.y = rel.y;
	screen_pos.x = (render->render_width * 0.5f) * (1.0f + cam_pos.x / cam_pos.z);
	screen_pos.y = (render->render_height * 0.5f) - (cam_pos.y / cam_pos.z);
	entity->transform.depth = cam_pos.z;
	entity->transform.x = screen_pos.x;
	entity->transform.y = screen_pos.y;
	entity->transform.width = fabs(render->render_height / cam_pos.z);
	entity->transform.height = fabs(render->render_height / cam_pos.z);
	draw_sprite_entity(entity->transform, &entity->spr, render);
}

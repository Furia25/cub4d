/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:39:13 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 16:33:46 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

void	entity_basic_draw(t_entity *entity, t_render_context *render)
{
	t_vec3				relative;
	t_vec3				cam_pos;
	t_vec2				projected;

	relative = vec3_sub(bbox_get_center(entity->hitbox),
			render->player->position);
	cam_pos.z = relative.x * render->yaw_cos + relative.y * render->yaw_sin;
	if (cam_pos.z <= 0.01 || cam_pos.z > RENDER_DISTANCE)
		return ;
	cam_pos.x = relative.y * render->yaw_cos - relative.x * render->yaw_sin;
	cam_pos.y = relative.z;
	projected.x = (cam_pos.x / cam_pos.z) * render->focal * render->ratio;
	projected.y = (cam_pos.y / cam_pos.z) * render->focal * render->ratio;
	entity->transform.x = (projected.x + 1.0f) * render->halfw;
	entity->transform.y = (1.0f - projected.y) * render->halfh;
	entity->transform.y += render->player->pitch_offset;
	entity->transform.scale = render->aspect_res * (2.f / cam_pos.z);
	entity->transform.x -= entity->spr.width * entity->transform.scale * 0.1;
	entity->transform.depth = sqrt(relative.x * relative.x
			+ relative.y * relative.y);
	draw_sprite(entity->transform, (t_sprite *)entity, render);
}

void	draw_interaction(t_render_context *ctx, t_game *game)
{
	t_button		btn;

	if (game->entity_manager.interacted && game->render_textbox)
	{
		if (key_is_pressed(KEY_INTERACT, game))
		{
			game->entity_manager.interacted = NULL;
			game->render_textbox = false;
			return ;
		}
		if (!game->entity_manager.interacted->data)
			return ;
		draw_textbox(ctx, game->entity_manager.interacted->data,
			game->entity_manager.interaction_time,
			(t_ivec2){MINIMAP_SIZE, game->win.height - MINIMAP_SIZE - 12});
	}
	else if (game->entity_manager.can_interact)
	{
		btn.x = (game->win.halfwidth - (S_BUTTON_INTERACT / 2));
		btn.y = (game->win.height * 0.85 - (S_BUTTON_INTERACT / 2));
		btn.width = S_BUTTON_INTERACT;
		btn.height = S_BUTTON_INTERACT;
		draw_interact_button(ctx, &btn, 0);
	}
}

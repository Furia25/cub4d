/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:50:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/08 00:12:02 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"
#include "cub3d_entities.h"

static inline void	render_rays(int start, int end, t_render_context *render);
static void		render_init(int width, int height,
						t_render_context *context, t_game *game);

void	render(t_game *game)
{
	t_parsing			*parsing;
	t_render_context	context;

	parsing = &game->parsing;
	render_init(game->win.width, game->win.height, &context, game);
	if (game->state == STATE_MENU || game->state == STATE_PAUSED)
	{
		render_menu(game->state == STATE_MENU, &context, game);
		return ;
	}
	entities_draw(game, &context);
	context.halfh = game->win.halfheight + game->player.pitch_offset;
	context.halfh = clamp(context.halfh, 0, game->win.height);
	render_rays(0, context.render_width, &context);
	render_skyfog(parsing->ambiant_color, parsing->ceil_color,
		parsing->ambiant_strength, &context);
	if (game->hud_cigarette.sprite.sheet.asset != game->textures[TEXTURE_ERROR])
		draw_sprite(game->hud_cigarette.sprite.transform,
			&game->hud_cigarette.sprite, &context);
	if (game->entity_manager.can_interact != NULL)
		draw_interaction(&context, game);
	if (key_check(KEY_TAB, game))
		draw_full_map(game);
	else
		draw_minimap(game);
}
static inline void	clear_zbuffer(float *zbuffer, int width, int height);

static void	render_init(int width, int height,
		t_render_context *ctx, t_game *game)
{
	ctx->z_buffer = game->z_buffer;
	clear_zbuffer(game->z_buffer, width, height);
	ctx->game = game;
	ctx->textures = game->textures;
	ctx->tilemap = game->tilemap;
	ctx->frame = game->frame;
	ctx->player = &game->player;
	ctx->position = vec3_to_vec2(game->player.position);
	ctx->direction = game->player.yaw_rad;
	ctx->render_height = height;
	ctx->render_width = width;
	ctx->eye_height = game->player.position.z;
	ctx->fov = deg_to_rad(game->player.fov_deg);
	ctx->fov_y = deg_to_rad(game->player.fov_deg - 15);
	ctx->halfw = game->win.halfwidth;
	ctx->halfh = game->win.halfheight;
	ctx->focal = 1.0f / tanf(ctx->fov * 0.70);
	ctx->proj_x = ctx->halfw / tanf(ctx->fov * .5f);
	ctx->proj_y = ctx->halfh / tanf(ctx->fov * .5f);
	ctx->yaw_cos = cosf(game->player.yaw_rad);
	ctx->yaw_sin = sinf(game->player.yaw_rad);
	ctx->ratio = (float)(ctx->render_width) / (float)(ctx->render_height);
	ctx->aspect_res = game->aspect_res;
}

static inline void	render_rays(int start, int end, t_render_context *render)
{
	t_ray2			ray;
	int				x;
	float			camera_x;
	float			ray_angle;

	x = start;
	while (x < end)
	{
		camera_x = 2.0 * x / (float)render->render_width - 1.0;
		ray_angle = render->direction + atan(camera_x * tan(render->fov / 2));
		ray = ray2_from_angle(render->position, ray_angle);
		render_ray(ray_angle, x, &ray, render);
		x++;
	}
}

static inline void	clear_zbuffer(float *zbuffer, int width, int height)
{
	size_t	index;
	size_t	size;

	index = 0;
	size = width * height;
	while (index < size)
		zbuffer[index++] = INFINITY;
}

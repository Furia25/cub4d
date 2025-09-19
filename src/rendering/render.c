/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:50:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/19 16:29:13 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"
#include "cub3d_entities.h"

static inline void	render_rays(int start, int end, t_render_context *render);
static void		render_init(int width, int height, \
	t_render_context *context, t_game *game);
static inline void	render_fog(t_render_context *render, t_parsing *parsing);

void	render(t_game *game)
{
	t_render_context	context;

	render_init(game->win_size.width, game->win_size.height, &context, game);
	entities_draw(game, &context);
	context.halfh = game->win_size.halfheight + game->player.pitch_offset;
	context.halfh = clamp(context.halfh, 0, game->win_size.height);
	render_rays(0, context.render_width, &context);
	render_fog(&context, &game->parsing);
	//render_sky(&context);
	game->cigarette.transform.index = clamp(get_elapsed_ms() / 50, 0, 149);
	draw_sprite(game->cigarette.transform, &game->cigarette, &context);
	draw_minimap(game);
	if (key_check(KEY_TAB, game))
		draw_full_map(game);
}
static void	render_init(int width, int height,
		t_render_context *ctx, t_game *game)
{
	ctx->z_buffer = game->z_buffer;
	for (int i = 0; i < width * height; i++)
		ctx->z_buffer[i] = INFINITY;
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
	ctx->halfw = game->win_size.halfwidth;
	ctx->halfh = game->win_size.halfheight;
	ctx->focal = 1.0f / tanf(ctx->fov * 0.75);
	ctx->proj_x = ctx->halfw / tanf(ctx->fov * .5f);
	ctx->proj_y = ctx->halfh / tanf(ctx->fov * .5f);
	ctx->yaw_cos = cosf(game->player.yaw_rad);
	ctx->yaw_sin = sinf(game->player.yaw_rad);
	ctx->ratio = (float)(ctx->render_width) / (float)(ctx->render_height);
	ctx->aspect_res = ctx->render_height / (float)ASPECT_RES;
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

static inline void	render_fog(t_render_context *render, t_parsing *parsing)
{
	uint16_t	fog;
	float		*zbuffer;
	int			x;
	int			y;

	y = 0;
	zbuffer = render->z_buffer;
	while (y < render->render_height)
	{
		x = 0;
		while (x < render->render_width)
		{
			fog = zbuffer[x + y * render->render_width] * parsing->fog_intensity;
			parsing->fog_color.channels.a = fog;
			if (fog >= 255)
				draw_pixel(parsing->c_color, x, y, render->frame);
			else
				draw_pixel(parsing->fog_color, x, y, render->frame);
			x++;
		}
		y++;
	}
}

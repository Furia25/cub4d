/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:50:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/25 00:55:02 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <immintrin.h>
#include "cub3d.h"
#include "cub3d_rendering.h"

static inline void	render_rays(int start, int end, t_render_context *render);
static void		render_init(int width, int height, \
	t_render_context *context, t_game *game);

void	render(t_game *game)
{
	t_render_context	context;

	render_init(game->w_width, game->w_height, &context, game);
	render_rays(0, context.render_width, &context);
	draw_minimap(game);
	manage_npcs(game);
	if (key_check(KEY_TAB, game))
		draw_full_map(game);
}
static void	render_init(int width, int height,
		t_render_context *context, t_game *game)
{
	context->z_buffer = game->z_buffer;
	ft_memset(context->z_buffer, UINT8_MAX, game->w_width * game->w_height);
	context->game = game;
	context->textures = game->textures;
	context->tilemap = game->tilemap;
	context->frame = game->frame;
	context->player = &game->player;
	context->position = vec3_to_vec2(game->player.position);
	context->direction = game->player.rad_direction;
	context->render_height = height;
	context->render_width = width;
	context->eye_height = game->player.position.z;
	context->fov = deg_to_rad(game->player.fov_deg);
	context->fov_x = context->fov;
	context->fov_y = deg_to_rad(game->player.fov_deg - 15);
	context->halfw = game->w_halfwidth;
	context->halfh = game->w_halfheight;
	context->proj_dist_x = context->halfw / tanf(context->fov_x * .5f);
	context->proj_dist_y = context->halfh / tanf(context->fov_y * .5f);
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

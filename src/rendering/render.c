/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:50:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/20 15:32:14 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static void			render_init(int width, int height,
		t_render_context *context, t_game *game);
static inline void	render_rays(int start, int end, t_render_context *render);

void	render(t_game *game)
{
	t_render_context	context;

	render_init(WINDOW_WIDTH, WINDOW_HEIGHT, &context, game);
	render_rays(0, context.render_width, &context);
	draw_minimap(game);
	draw_enemies(game);
	handle_full_map(game);
}

static void	render_init(int width, int height, t_render_context *context, t_game *game)
{
	context->game = game;
	context->tilemap = game->tilemap;
	context->frame = game->img;
	context->player = &game->player;
	context->position = game->player.position;
	context->direction = game->player.rad_direction;
	context->render_height = height;
	context->render_width = width;
	context->eye_height = game->player.height;
	context->fov = deg_to_rad(game->player.fov_deg);
	context->fov_x = context->fov;
	context->fov_y = deg_to_rad(game->player.fov_deg - 15);
	context->halfw = WINDOW_WIDTH * .5f;
	context->halfh = WINDOW_HEIGHT * .5f;
	context->proj_dist_x = context->halfw / tanf(context->fov_x  * .5f);
	context->proj_dist_y = context->halfh / tanf(context->fov_y  * .5f);
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
		camera_x = 2.0 * x / (float)WINDOW_WIDTH - 1.0;
		ray_angle = render->direction + atan(camera_x * tan(render->fov / 2));
		ray = ray2_from_angle(render->position, ray_angle);
		render_ray(ray_angle, x, &ray, render);
		x++;
	}
}

static void	init_texture_ctx(t_texture_context *tex_ctx, float dist, int column)
{
	tex_ctx->wall_height = WINDOW_HEIGHT / dist;
	tex_ctx->wall_start = clamp(-tex_ctx->wall_height \
		/ 2 + WINDOW_HEIGHT / 2, 0, WINDOW_HEIGHT);
	tex_ctx->wall_end = clamp(tex_ctx->wall_height \
		/ 2 + WINDOW_HEIGHT / 2, 0, WINDOW_HEIGHT);
	tex_ctx->column = column;
}

static void	set_texture_orientation(t_raycast_hit *result)
{
	if (result->orientation == 0 && result->original_ray.dir_normal.x < 0)
		result->tile_info.texture = TEXTURE_WEST;
	else if (result->orientation == 0 && result->original_ray.dir_normal.x > 0)
		result->tile_info.texture = TEXTURE_EAST;
	else if (result->orientation == 1 && result->original_ray.dir_normal.y < 0)
		result->tile_info.texture = TEXTURE_NORTH;
	else if (result->orientation == 1 && result->original_ray.dir_normal.y > 0)
		result->tile_info.texture = TEXTURE_SOUTH;
}

static void	render_ray(float ray_angle, int column,
		t_raycast_hit *result, t_render_context *ctx)
{
	float				corrected_dist;
	int					y;
	t_texture_context	tex_ctx;
	
	corrected_dist = result->dist * cosf(ray_angle - ctx->direction);
	init_texture_ctx(&tex_ctx, corrected_dist, column);
	set_texture_orientation(result);
	result->pos.x = result->original_ray.origin.x \
				+ result->original_ray.dir_normal.x * result->dist;
	result->pos.y = result->original_ray.origin.y \
				+ result->original_ray.dir_normal.y * result->dist;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < tex_ctx.wall_start)
			img_draw_pixel(ctx->game->c_color, column, y, ctx->frame);
		else if (y > tex_ctx.wall_end)
			img_draw_pixel(ctx->game->f_color, column, y, ctx->frame);
		else
			manage_texture(result, ctx, &tex_ctx, &y);
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:25:18 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/20 15:31:33 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static inline void	raycast_init(t_raycast_context *ctx);
static inline void	raycast_launch(t_raycast_context *ctx);
static inline bool	check_wall_tile(t_raycast_hit *hit,
		t_raycast_context *ctx);
static inline void	raycast_set_dist(t_raycast_hit *hit,
		t_raycast_context *ctx);

void	render_ray(float base_angle, int column,
		t_ray2 *ray, t_render_context *render_ctx)
{
	t_raycast_context	ctx;

	ctx.actual.original_angle = base_angle;
	ctx.actual.original_ray = *ray;
	ctx.column = column;
	ctx.render_ctx = render_ctx;
	ctx.ray = ray;
	ctx.tilemap = render_ctx->tilemap;
	ctx.step.x = sign(ray->dir_normal.x);
	ctx.step.y = sign(ray->dir_normal.y);
	ctx.last_end = 0;
	ctx.last_start = WINDOW_HEIGHT;
	raycast_init(&ctx);
	raycast_launch(&ctx);
}

static inline void	raycast_init(t_raycast_context *ctx)
{
	t_ray2	*ray;

	ray = ctx->ray;
	ctx->actual_tile.x = (int)(ray->origin.x);
	ctx->actual_tile.y = (int)(ray->origin.y);
	if (float_equal(ray->dir_normal.x, 0))
		ctx->delta_dist.x = INFINITY;
	else
		ctx->delta_dist.x = fabs(1 / ray->dir_normal.x);
	if (float_equal(ray->dir_normal.y, 0))
		ctx->delta_dist.y = INFINITY;
	else
		ctx->delta_dist.y = fabs(1 / ray->dir_normal.y);
	if (ray->dir_normal.x < 0.0)
		ctx->step_dist.x = 
			(ray->origin.x - ctx->actual_tile.x) * ctx->delta_dist.x;
	else
		ctx->step_dist.x = 
			(ctx->actual_tile.x + 1.0 - ray->origin.x) *  ctx->delta_dist.x;
	if (ray->dir_normal.y < 0.0)
		ctx->step_dist.y = 
			(ray->origin.y - ctx->actual_tile.y) * ctx->delta_dist.y;
	else
		ctx->step_dist.y = 
			(ctx->actual_tile.y + 1.0 - ray->origin.y) *  ctx->delta_dist.y;
}

static inline void	raycast_launch(t_raycast_context *ctx)
{
	while (fmin(ctx->step_dist.x, ctx->step_dist.y) < RENDER_DISTANCE)
	{
		if (ctx->step_dist.x < ctx->step_dist.y)
		{
			ctx->step_dist.x += ctx->delta_dist.x;
			ctx->actual_tile.x += ctx->step.x;
			ctx->actual.orientation = 0;
		}
		else
		{
			ctx->step_dist.y += ctx->delta_dist.y;
			ctx->actual_tile.y += ctx->step.y;
			ctx->actual.orientation = 1;
		}
		if (check_wall_tile(&ctx->actual, ctx))
		{
			raycast_set_dist(&ctx->actual, ctx);
			render_draw_ray(&ctx->actual, ctx, ctx->render_ctx);
		}
	}
}

static inline bool	check_wall_tile(t_raycast_hit *hit,
		t_raycast_context *ctx)
{
	t_tile	*tile;
	int		tile_x;
	int		tile_y;

	tile_x = ctx->actual_tile.x;
	tile_y = ctx->actual_tile.y;
	if (!tilemap_is_tile_valid(tile_x, tile_y, ctx->tilemap))
		return (false);
	tile = tilemap_get_tile(tile_x, tile_y, ctx->tilemap);
	hit->tile_info = &tile->info;
	hit->tile = tile;
	if (hit->tile_info->wall)
		return (true);
	return (false);
}

static inline void	raycast_set_dist(t_raycast_hit *hit,
		t_raycast_context *ctx)
{
	if (hit->orientation == 0)
		hit->dist = (ctx->actual_tile.x - ctx->ray->origin.x
			+ (1 - ctx->step.x) * 0.5) / ctx->ray->dir_normal.x;
	else
		hit->dist = (ctx->actual_tile.y - ctx->ray->origin.y
			+ (1 - ctx->step.y) * 0.5) / ctx->ray->dir_normal.y;
	
}

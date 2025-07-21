/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floorcast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:25:20 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/21 21:57:23 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_rendering.h"

void	render_floor(t_render_context *r_ctx, t_ray2 ray,
			float angle, int column)
{
	t_tile				*tile;
	float				real_dist;
	t_vec2				tile_pos;
	int					y;

	y = r_ctx->halfh;
	while (y <= r_ctx->render_height)
	{
		real_dist = r_ctx->proj_dist_y
			* ((r_ctx->eye_height) / (y - r_ctx->halfh))
			* (1.0f / cosf(angle - r_ctx->direction));
		tile_pos.x = ray.origin.x + ray.dir_normal.x * real_dist;
		tile_pos.y = ray.origin.y + ray.dir_normal.y * real_dist;
		if (real_dist == NAN)
			return ;
		if (!tilemap_is_tile_valid(tile_pos.x, tile_pos.y, r_ctx->tilemap))
		{
			y++;
			continue ;
		}
		tile = &r_ctx->tilemap->tiles[(size_t)tile_pos.y][(size_t)tile_pos.x];
		real_dist = r_ctx->proj_dist_y
			* ((r_ctx->eye_height ) / (y - r_ctx->halfh))
			* (1.0f / cosf(angle - r_ctx->direction));
		tile_pos.x = ray.origin.x + ray.dir_normal.x * real_dist;
		tile_pos.y = ray.origin.y + ray.dir_normal.y * real_dist;
		render_horizontal_texture((t_ivec2){column, y},
			tile_pos, r_ctx, tile->info.texture);
		y++;
	}
}

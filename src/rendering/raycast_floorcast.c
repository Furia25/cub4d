/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floorcast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:25:20 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/21 17:40:30 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_rendering.h"

void	render_floor(t_render_context *r_ctx, t_ray2 ray, float angle, int column)
{
	float				real_dist;
	t_vec2				tile_pos;
	int					y;

	y = r_ctx->halfh;
	while (y < r_ctx->render_height)
	{
		real_dist = fabsf(r_ctx->proj_dist_y \
		* ((r_ctx->halfh) / (y - r_ctx->halfh)) \
		* (1.0f / cosf(angle - r_ctx->direction)));
		tile_pos.x = ray.origin.x + ray.dir_normal.x * real_dist;
		tile_pos.y = ray.origin.y + ray.dir_normal.y * real_dist;
		render_horizontal_texture((t_ivec2){column, y}, 
			tile_pos, r_ctx, TEXTURE_TOP);
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:41:26 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/20 15:41:28 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_rendering.h"
#include "cub3d.h"

static void	render_texture(t_png *texture, t_texture_context *tex_ctx, \
	t_render_context *ctx, int *row)
{
	int		tex_y;
	float	tex_pos;
	float	step;

	tex_pos = 0;
	step = 498 / (float)tex_ctx->wall_height;
	while (*row < tex_ctx->wall_end)
	{
		tex_y = (int)tex_pos;
		img_draw_pixel(texture->pixels_8bit[tex_y * 498 + tex_ctx->tex_x], \
			tex_ctx->column, *row, ctx->frame);
		tex_pos += step;
		(*row)++;
	}
}

void	manage_texture(t_raycast_hit *result, t_render_context *ctx, \
	t_texture_context *tex_ctx, int *row)
{
	t_png	*texture;
	int		tex_x;
	float	offset;

	texture = ctx->game->textures[result->tile_info->texture];
	if (!result->orientation)
		offset = result->pos.y - (int)result->pos.y;
	else
		offset = result->pos.x - (int)result->pos.x;
	tex_x = (int)(offset * 498);
	if ((result->orientation == 0 && result->original_ray.dir_normal.x > 0) || \
		(result->orientation == 1 && result->original_ray.dir_normal.y < 0))
		tex_x = 498 - tex_x;
	tex_ctx->tex_x = tex_x;
	if (*row < 1)
		*row = (WINDOW_HEIGHT - tex_ctx->wall_height) / 2;
	render_texture(texture, tex_ctx, ctx, row);
}

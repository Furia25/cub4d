/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:41:26 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/16 15:18:32 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_rendering.h"
#include "cub3d.h"

void render_texture(t_raycast_hit *result, t_render_context *ctx, int column, int *row, int wall_end, int wall_height)
{
	t_png	*texture;
	int		tex_x;
	int		tex_y;
	float	step;
	float	tex_pos;
	float 	offset;

 	texture = ctx->game->textures[result->tile_info.texture];
	if (!result->orientation)
		offset = result->pos.y - (int)result->pos.y;
	else
		offset = result->pos.x - (int)result->pos.x;
	tex_x = (int)(offset * 498);
	if ((result->orientation == 0 && result->original_ray.dir_normal.x > 0) ||
		(result->orientation == 1 && result->original_ray.dir_normal.y < 0))
		tex_x = 498 - tex_x;
	step = 498 / (float)wall_height;
	tex_pos = 0;
	while (*row < wall_end)
	{
		tex_y = (int)tex_pos;
		img_draw_pixel(texture->pixels_8bit[tex_y * 498 + tex_x], column, *row, ctx->frame);
		tex_pos += step;
		(*row)++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:41:26 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/24 17:42:28 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_rendering.h"
#include "cub3d.h"

/*
STARTING FROM TOP WALL
*/
// static void	render_texture(t_texture_context *tex_ctx,
// 	t_raycast_hit *hit, t_raycast_context *ctx, uint8_t *zbuf)
// {
// 	int		buffer_idx;
// 	int		tex_y;
// 	int		tex_x;
// 	float	tex_pos;
// 	float	step;

// 	step = tex_ctx->texture->header.height / (float)tex_ctx->wall_height;
// 	tex_pos = (tex_ctx->wall_start - tex_ctx->wall_start_actual) * step;
// 	tex_x = tex_ctx->tex_x % tex_ctx->texture->header.width;
// 	tex_ctx->y = tex_ctx->wall_start;
// 	while (tex_ctx->y < tex_ctx->wall_end)
// 	{
// 		buffer_idx = tex_ctx->y * WINDOW_WIDTH + ctx->column;
// 		tex_y = ((int)tex_pos) % tex_ctx->texture->header.height;
// 		if (hit->dist < zbuf[buffer_idx])
// 		{
// 			draw_pixel(tex_ctx->texture->pixels_8bit[tex_y * tex_ctx->texture->header.width + tex_x], 
// 				ctx->column, tex_ctx->y, ctx->render_ctx->frame);
// 			zbuf[buffer_idx] = hit->dist;
// 		}
// 		tex_pos += step;
// 		tex_ctx->y++;
// 	}
// }


/*
STARTING FROM BOTTOM WALL BUT INCORRECT TEX_POS / TEX_Y
*/
// static void	render_texture(t_texture_context *tex_ctx,
// 	t_raycast_hit *hit, t_raycast_context *ctx, uint8_t *zbuf)
// {
// 	int		buffer_idx;
// 	int		tex_y;
// 	int		tex_x;
// 	float	tex_pos;
// 	float	step;

// 	step = tex_ctx->texture->header.height / (float)tex_ctx->wall_height;
// 	tex_pos = (tex_ctx->wall_end - tex_ctx->wall_end_actual) * step;
// 	tex_x = tex_ctx->tex_x % tex_ctx->texture->header.width;
// 	tex_ctx->y = tex_ctx->wall_end;
// 	while (tex_ctx->y > tex_ctx->wall_start)
// 	{
// 		buffer_idx = tex_ctx->y * WINDOW_WIDTH + ctx->column;
// 		tex_y = ((int)tex_pos) % tex_ctx->texture->header.height;
// 		if (hit->dist < zbuf[buffer_idx])
// 		{
// 			draw_pixel(tex_ctx->texture->pixels_8bit[tex_y * tex_ctx->texture->header.width + tex_x], 
// 				ctx->column, tex_ctx->y, ctx->render_ctx->frame);
// 			zbuf[buffer_idx] = hit->dist;
// 		}
// 		tex_pos -= step;
// 		tex_ctx->y--;
// 	}
// }


/*
WORKING BUT LAGGY
*/
// static void	render_texture(t_texture_context *tex_ctx,
// 	t_raycast_hit *hit, t_raycast_context *ctx, uint8_t *zbuf)
// {
// 	int		buffer_idx;
// 	int		tex_y;
// 	float	tex_pos;
// 	float	step;

// 	step = tex_ctx->texture->header.height / (float)tex_ctx->wall_height;
// 	tex_pos = tex_ctx->texture->header.height - ((tex_ctx->wall_end_actual - tex_ctx->wall_end) * step);
// 	tex_ctx->y = tex_ctx->wall_end;
// 	while (tex_ctx->y > tex_ctx->wall_start)
// 	{
// 		buffer_idx = tex_ctx->y * WINDOW_WIDTH + ctx->column;
// 		tex_y = (int)(fmod(tex_pos, tex_ctx->texture->header.height));
// 		if (tex_y < 0)
// 			tex_y += tex_ctx->texture->header.height;
// 		if (hit->dist < zbuf[buffer_idx])
// 		{
// 			draw_pixel(tex_ctx->texture->pixels_8bit[tex_y * tex_ctx->texture->header.width + tex_ctx->tex_x], 
// 				ctx->column, tex_ctx->y, ctx->render_ctx->frame);
// 			zbuf[buffer_idx] = hit->dist;
// 		}
// 		tex_pos -= step;
// 		tex_ctx->y--;
// 	}
// }


/*
TEST
*/
static void	render_texture(t_texture_context *tex_ctx,
	t_raycast_hit *hit, t_raycast_context *ctx, uint8_t *zbuf)
{
	int		buffer_idx;
	int		tex_y;
	float	tex_pos;
	float	step;

	step = tex_ctx->texture->header.height / (float)tex_ctx->wall_height;
	tex_pos = tex_ctx->texture->header.height - ((tex_ctx->wall_end_actual - tex_ctx->wall_end) * step);
	tex_ctx->y = tex_ctx->wall_end;
	while (tex_ctx->y > tex_ctx->wall_start)
	{
		buffer_idx = tex_ctx->y * WINDOW_WIDTH + ctx->column;
		tex_y = (int)(tex_pos - (tex_ctx->texture->header.height * floorf(tex_pos / tex_ctx->texture->header.height)));
		if (hit->dist < zbuf[buffer_idx])
		{
			draw_pixel(tex_ctx->texture->pixels_8bit[tex_y * tex_ctx->texture->header.width + tex_ctx->tex_x], 
				ctx->column, tex_ctx->y, ctx->render_ctx->frame);
			zbuf[buffer_idx] = hit->dist;
		}
		tex_pos -= step;
		tex_ctx->y--;
	}
}

void	manage_texture(t_raycast_hit *hit, t_raycast_context *ctx, 
	t_render_context *render, t_texture_context	*tex_ctx)
{
	uint8_t		*zbuf;
	float		offset;

	zbuf = ctx->render_ctx->z_buffer;
	tex_ctx->texture = render->game->textures[hit->tile_info->texture];
	if (!hit->orientation)
		offset = hit->pos.y - (int)hit->pos.y;
	else
		offset = hit->pos.x - (int)hit->pos.x;
	tex_ctx->tex_x = (int)(offset * tex_ctx->texture->header.width);
	if ((hit->orientation == 0 && hit->original_ray.dir_normal.x > 0) || 
		(hit->orientation == 1 && hit->original_ray.dir_normal.y < 0))
		tex_ctx->tex_x = tex_ctx->texture->header.width - tex_ctx->tex_x - 1;
	render_texture(tex_ctx, hit, ctx, zbuf);
}
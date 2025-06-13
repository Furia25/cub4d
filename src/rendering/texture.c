/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:41:26 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/13 14:33:32 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_rendering.h"
#include "cub3d.h"

void	render_texture(t_raycast_hit *result, t_render_context *context, int collumn, int *row, int wall_end)
{
	t_png	*texture;
	int		i;
	float	offset;

	if (result->orientation)
		offset = result->pos.y - (int)result->pos.y;
	else
		offset = result->pos.x - (int)result->pos.x;
	offset *= 498;
	texture = result->tilemap->textures.wall;
	i = 0;
	while (*row < wall_end)
	{
		// img_draw_pixel(rgba8(220, 0, 255 - 80 * result->orientation, 255),
		// 			collumn, *row, context->frame);
		img_draw_pixel(texture->pixels_8bit[(int)offset + (498 * i)], collumn, *row, context->frame);
		i++;
		(*row)++;
	}
}

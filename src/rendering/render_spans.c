/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_spans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:56:13 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/15 20:27:20 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_rendering.h"

static t_area	g_areas[MAX_AREAS] = {0};
static size_t	g_areas_used = 0;

void	areas_init(void)
{
	g_areas_used = 0;
}

#define EMPTY_Y_START  (WINDOW_HEIGHT + 1)
		
void	areas_add(float height, t_texture_type texture,
		int column, t_span span)
{
	size_t	index;
	t_area	*area;
	t_span	*actual_sp;

	index = 0;
	while (index < g_areas_used)
	{
		area = &g_areas[index];
		actual_sp = &area->spans[column + 1];
		if (height != area->height || texture != area->texture)
		{
			index++;
			continue;
		}
		if (actual_sp->y_start != -1)
		{
			if (span.y_end == actual_sp->y_start)
				actual_sp->y_start = span.y_start;
			else if (span.y_start == actual_sp->y_end)
				actual_sp->y_end = span.y_end;
		}
		else
		{
			actual_sp->y_start = span.y_start;
			actual_sp->y_end   = span.y_end;
			if (column < area->min)
				area->min = column;
			if (column > area->max)
				area->max = column;
		}
		return ;
	}
	if (g_areas_used < MAX_AREAS)
	{
		area = &g_areas[g_areas_used++];
		area->height  = height;
		area->texture = texture;
		area->min     = column;
		area->max     = column;
		index = 0;
		while (index < WINDOW_WIDTH + 2)
		{
			area->spans[index].y_start = -1;
			area->spans[index].y_end   = -1;
			index++;
		}
		area->spans[column + 1] = span;
	}
}



void	render_ceil_floor(t_render_context *render)
{
	size_t	area_index;
	t_area	*area;
	int		x;
	t_span	*span;
	int		y;

	area_index = 0;
	while (area_index < g_areas_used)
	{
		area = &g_areas[area_index];
		x = area->min;
		while (x <= area->max)
		{
			span = &area->spans[x + 1];
			if (span->y_start <= span->y_end)
			{
				y = span->y_start;
				while (y < span->y_end)
				{
					draw_pixel(rgba8(125, 200, 55, 125),
						x, y, render->frame);
					y++;
				}
			}
			x++;
		}
		area_index++;
	}
}

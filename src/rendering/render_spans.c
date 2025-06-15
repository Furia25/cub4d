/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_spans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:56:13 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/16 00:36:24 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_rendering.h"

static t_area	g_areas[MAX_AREAS] = {0};
static size_t	g_areas_used = 0;
static int		g_span_start[WINDOW_HEIGHT] = {0};

void	areas_add(float height, t_texture_type texture,
		int column, t_span span)
{
	size_t	index;
	t_area	*area;
	t_span	*actual_sp;

	column += 1;
	index = 0;
	while (index < g_areas_used)
	{
		area = &g_areas[index++];
		if (area->height != height || area->texture != texture)
			continue;
		actual_sp = &area->spans[column];
		if (actual_sp->start != AREA_EMPTY)
		{
			if (span.start <= actual_sp->end + 1 && actual_sp->start <= span.end + 1) {
				actual_sp->start = min(actual_sp->start, span.start);
				actual_sp->end   = max(actual_sp->end,   span.end);
				return;
			}
			continue;
		}
		else
			break ;
	}
	if (g_areas_used < MAX_AREAS)
	{
		area = &g_areas[g_areas_used++];
		area->height = height;
		area->texture = texture;
		area->min = WINDOW_WIDTH;
		area->max = -1;
		index = 0;
		while (index < WINDOW_WIDTH + 2)
		{
			area->spans[index].start = AREA_EMPTY;
			index++;
		}
	}
	area->spans[column] = span;
	if (column < area->min)
		area->min = column;
	if (column > area->max)
		area->max = column;
}

static inline void	area_span_draw(t_span span_x, int y,
		t_area *area, t_render_context *render);
static inline void create_horizontals(int x, t_area *area,
		t_render_context *render);

void	render_ceil_floor(t_render_context *render)
{
	size_t	index;
	t_area	*area;
	int		x;

	index = 0;
	while (index < g_areas_used)
	{
		area = &g_areas[index++];
		if (area->min > area->max)
			continue ;
		x = area->min;
		while (x < area->max + 2)
		{
			create_horizontals(x, area, render);
			x++;
		}
	}
	g_areas_used = 0;
	index = 0;
	while (index < WINDOW_HEIGHT)
	{
		g_span_start[index] = AREA_EMPTY;
		index++;
	}
}

static inline void create_horizontals(int x, t_area *area,
		t_render_context *render)
{
	t_span	*pre;
	t_span	*actual;
	int		y;

	pre = &area->spans[x - 1];
	actual = &area->spans[x];
	if (pre->start == AREA_EMPTY || actual->start == AREA_EMPTY)
        return;
	y = pre->start;
	while (y < actual->start && y <= pre->end)
		area_span_draw((t_span){g_span_start[y], x - 1}, y++, area, render);
	y = pre->end;
	while (y > actual->end && y >= pre->start)
		area_span_draw((t_span){g_span_start[y], x - 1}, y--, area, render);
	y = actual->start;
	while (y < pre->start && y <= actual->end)
		g_span_start[y++] = x - 1;
	y = actual->end;
	while (y > pre->end && y >= actual->start)
		g_span_start[y--] = x - 1;
}

static inline void	area_span_draw(t_span span_x, int y,
		t_area *area, t_render_context *render)
{
	while (span_x.start <= span_x.end)
	{
		draw_pixel(rgba8(255, 0 + 125 * area->texture, 0, 200), span_x.start, y, render->frame);
		span_x.start++;
	}
}

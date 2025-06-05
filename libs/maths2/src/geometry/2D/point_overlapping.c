/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_overlapping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:06:46 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 22:56:36 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2_geometry.h"

bool	point_in_rect_b(t_vec2 point, const t_rect_bounds rb)
{
	return (point.x >= rb.min.x
		&& point.x <= rb.max.x
		&& point.y >= rb.min.y
		&& point.y <= rb.max.y
	);
}

bool	point_in_rect(t_vec2 point, const t_rect r)
{
	return (point.x >= r.pos.x
		&& point.x <= r.pos.x + r.size.x
		&& point.y >= r.pos.y
		&& point.y <= r.pos.y + r.size.y
	);
}

bool	point_in_circle(t_vec2 p, const t_circle c)
{
	float	dx;
	float	dy;

	dx = p.x - c.pos.x;
	dy = p.y - c.pos.y;
	return (dx * dx + dy * dy <= (c.radius * c.radius));
}

static float	signed_area(t_vec2 p1, t_vec2 p2, t_vec2 p3)
{
	return ((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y));
}

bool	point_in_triangle(t_vec2 p, const t_triangle t)
{
	float	d1;
	float	d2;
	float	d3;
	bool	has_neg;
	bool	has_pos;

	d1 = signed_area(p, t.a, t.b);
	d2 = signed_area(p, t.b, t.c);
	d3 = signed_area(p, t.c, t.a);
	has_neg = (d1 < 0.0f) || (d2 < 0.0f) || (d3 < 0.0f);
	has_pos = (d1 > 0.0f) || (d2 > 0.0f) || (d3 > 0.0f);
	return (!(has_neg && has_pos));
}

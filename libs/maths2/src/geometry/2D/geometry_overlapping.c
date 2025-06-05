/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_overlapping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:06:09 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/04 23:42:29 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths2.h"
#include "maths2_geometry.h"

bool	circle_in_rect(t_circle c, t_rect r)
{
	float	cx;
	float	cy;
	float	dx;
	float	dy;

	cx = fmaxf(r.pos.x, fminf(c.pos.x, r.pos.x + r.size.x));
	cy = fmaxf(r.pos.y, fminf(c.pos.y, r.pos.y + r.size.y));
	dx = c.pos.x - cx;
	dy = c.pos.y - cy;
	return (dx * dx + dy * dy <= c.radius * c.radius);
}

bool	circle_in_circle(t_circle a, t_circle b)
{
	float	dx;
	float	dy;
	float	r;

	dx = a.pos.x - b.pos.x;
	dy = a.pos.y - b.pos.y;
	r = a.radius + b.radius;
	return (dx * dx + dy * dy <= r * r);
}

bool	rect_in_rect(t_rect a, t_rect b)
{
	return (
		a.pos.x < b.pos.x + b.size.x
		&& a.pos.x + a.size.x > b.pos.x
		&& a.pos.y < b.pos.y + b.size.y
		&& a.pos.y + a.size.y > b.pos.y
	);
}

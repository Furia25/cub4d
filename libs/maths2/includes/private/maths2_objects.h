/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_objects.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 01:50:18 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/06 19:16:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_OBJECTS_H
# define MATHS2_OBJECTS_H

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_ivec2
{
	int	x;
	int	y;
}	t_ivec2;

typedef struct s_ivec3
{
	int	x;
	int	y;
	int	z;
}	t_ivec3;

/*
Types representing 2D objects should be reserved for this usage.
*/

typedef struct s_ray2
{
	t_vec2	origin;
	t_vec2	dir_normal;
}	t_ray2;

typedef struct s_circle
{
	t_vec2	pos;
	double	radius;
}	t_circle;

typedef struct s_rect
{
	t_vec2	pos;
	t_vec2	size;
}	t_rect;

typedef struct s_rect_bounds
{
	t_vec2	min;
	t_vec2	max;
}	t_rect_bounds;

typedef struct s_triangle
{
	t_vec2	a;
	t_vec2	b;
	t_vec2	c;
}	t_triangle;

/***************************************************************/

/*
Types representing 3D objects should be reserved for this usage.
*/

typedef struct s_ray3
{
	t_vec3	origin;
	t_vec3	dir_normal;
}	t_ray3;

typedef struct s_plane3
{
	t_vec3	normal;
	float	d;
}	t_plane3;

typedef struct s_sphere
{
	t_vec3	pos;
	double	radius;
}	t_sphere;

typedef struct s_bbox
{
	t_vec3	min;
	t_vec3	max;
}	t_bbox;

typedef struct s_triangle3
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
}	t_triangle3;

/***************************************************************/

typedef struct s_quaternion
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_quaternion;

#endif
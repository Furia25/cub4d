/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2_geometry.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:24:28 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/05 19:24:54 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS2_GEOMETRY_H
# define MATHS2_GEOMETRY_H
# include "maths2.h"
# include "private/maths2_objects.h"
# include "maths2_vectors.h"
# include "private/maths2_constructors.h"
# include "private/maths2_constructors2.h"

# ifdef _USE_STANDARD_MATH

float	point_direction2d(t_vec2 origin, t_vec2 target);
# endif

/*2D RAYS*/

t_ray2	ray2_from_angle(t_vec2 origin, float angle);
t_ray2	ray2_from_points(t_vec2 origin, t_vec2 target);
t_vec2	ray2_point_at(t_ray2 ray, float t);

/*3D RAYS*/

t_ray3	ray3_from_points(t_vec3 origin, t_vec3 target);
t_ray3	ray3_from_direction(t_vec3 origin, t_vec3 direction);
t_vec3	ray3_point_at(t_ray3 ray, float t);

/*Functions to operate on 2D objects*/

t_rect	rect_from_rectb(const t_rect_bounds rectb);

bool	point_in_rect_b(t_vec2 point, const t_rect_bounds rb);
bool	point_in_rect(t_vec2 point, const t_rect r);
bool	point_in_triangle(t_vec2 point, const t_triangle t);
bool	point_in_circle(t_vec2 point, const t_circle c);

bool	rect_in_rect(t_rect a, t_rect b);
bool	circle_in_circle(t_circle a, t_circle b);
bool	circle_in_rect(t_circle c, t_rect r);

/*Functions to operate on 3D objects*/

float	point_plane_signed_distance(t_vec3 point, t_plane3 plane);
t_vec3	project_point_on_plane(t_vec3 point, t_plane3 plane);

bool	point_in_plane3(t_vec3 point, t_plane3 plane);
bool	point_in_bbox(t_vec3 point, t_bbox bbox);
bool	point_in_sphere(t_vec3 point, t_sphere sphere);
bool	point_in_triangle3(t_vec3 point, t_triangle3 triangle);

bool	bbox_in_bbox(const t_bbox b1, const t_bbox b2);
bool	sphere_in_sphere(const t_sphere s1, const t_sphere s2);
bool	sphere_in_bbox(const t_sphere sphere, const t_bbox bbox);

#endif
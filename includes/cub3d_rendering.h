/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_rendering.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:21:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/09 15:33:22 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_RENDERING_H
# define CUBE3D_RENDERING_H
# include "maths2_vectors.h"
# include "tilemap.h"

# define RENDER_DISTANCE	100

typedef struct s_raycast_hit
{
	t_ray2		original_ray;
	bool		hitted;
	int			orientation;
	double		dist;
	t_vec2		pos;
	t_tile_info	tile_info;
	t_tile_type	tile_type;
	t_tilemap	*tilemap;
}	t_raycast_hit;

t_raycast_hit	raycast_tilemap(t_ray2 *ray, t_tilemap *tilemap);

#endif
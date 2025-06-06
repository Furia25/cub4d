/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_rendering.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:21:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/06 22:29:49 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_RENDERING_H
# define CUBE3D_RENDERING_H
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
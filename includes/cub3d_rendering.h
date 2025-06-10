/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_rendering.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:21:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/10 20:08:25 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_RENDERING_H
# define CUBE3D_RENDERING_H
# include "maths2_vectors.h"
# include "tilemap.h"
# include "cub3d.h"

typedef struct s_render_context
{
	t_game		*game;
	t_img_data	*frame;
	t_player	*player;
	t_vec2		position;
	int			render_width;
	int			render_height;
	float		fov;
	float		direction;
}	t_render_context;

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

void			render_rays(int start_x, int end_x, t_render_context *render);
void			render(t_game *game);

#endif
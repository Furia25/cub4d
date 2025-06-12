/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_rendering.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:21:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/12 23:17:27 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_RENDERING_H
# define CUBE3D_RENDERING_H
# include "maths2_vectors.h"
# include "tilemap.h"
# include "cub3d.h"

# define RENDER_DISTANCE	100
# define MAX_HITS			100

typedef struct s_render_context
{
	t_game		*game;
	t_img_data	*frame;
	t_player	*player;
	t_tilemap	*tilemap;
	t_vec2		position;
	int			render_width;
	int			render_height;
	float		fov;
	float		fov_x;
	float		fov_y;
	float		proj_dist_x;
	float		proj_dist_y;
	float		eye_height;
	float		direction;
}	t_render_context;

typedef struct s_raycast_hit
{
	t_ray2		original_ray;
	float		original_angle;
	int			orientation;
	double		dist;
	t_tile_data	*tile_info;
	t_tile		*tile;
}	t_raycast_hit;

typedef struct s_raycast_buffer
{
	t_raycast_hit	hits[MAX_HITS];
	size_t			n_hits;
}	t_raycast_buffer;

typedef struct s_raycast_context
{
	t_render_context	*render_ctx;
	t_ray2				*ray;
	t_tilemap			*tilemap;
	t_raycast_hit		*result;
	t_raycast_buffer	buffer;
	t_ivec2				actual_tile;
	t_vec2				delta_dist;
	t_vec2				step_dist;
	t_ivec2				step;
	int					column;
}   t_raycast_context;

void	render(t_game *game);
void	render_rays(int start_x, int end_x, t_render_context *render);
void	render_ray(float base_angle, int column,
		t_ray2 *ray, t_render_context *render_ctx);
void	render_draw_ray(float ray_angle, int column,
		t_raycast_hit *result, t_render_context *context);

#endif
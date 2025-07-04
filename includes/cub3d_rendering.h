/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_rendering.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:21:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/04 11:26:53 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_RENDERING_H
# define CUB3D_RENDERING_H
# include "maths2_vectors.h"
# include "tilemap.h"
# include "cub3d.h"
# include "cub3d_textures.h"

# define RENDER_DISTANCE	200

typedef struct s_render_context
{
	uint8_t		*z_buffer;
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
	int			halfh;
	int			halfw;
	float		eye_height;
	float		direction;
}	t_render_context;

typedef struct s_raycast_hit
{
	t_vec2		pos;
	t_ray2		original_ray;
	float		original_angle;
	short		orientation;
	double		dist;
	int			tile_x;
	int			tile_y;
	t_tile_data	*tile_info;
	t_tile		*tile;
}	t_raycast_hit;

typedef struct s_raycast_context
{
	t_render_context	*render_ctx;
	t_ray2				*ray;
	t_tilemap			*tilemap;
	t_raycast_hit		actual;
	t_ivec2				actual_tile;
	t_vec2				delta_dist;
	t_vec2				step_dist;
	t_ivec2				step;
	int					column;
}	t_raycast_context;

void	render_ray(float base_angle, int column, \
	t_ray2 *ray, t_render_context *render_ctx);
void	render_draw_ray(t_raycast_hit *actual, \
	t_raycast_context *ctx, t_render_context *render);
void	manage_texture(t_raycast_hit *hit, t_raycast_context *ctx, \
	t_render_context *render, t_texture_context	*tex_ctx);
void	render_horizontal_texture(t_horizontal_tex *t_ctx, t_raycast_hit *hit, \
	t_render_context *r_ctx);

#endif
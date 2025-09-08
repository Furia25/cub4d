/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_rendering.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:21:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/08 16:50:37 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_RENDERING_H
# define CUB3D_RENDERING_H
# include "maths2_vectors.h"
# include "tilemap.h"
# include "cub3d.h"
# include "cub3d_textures.h"

# define RENDER_DISTANCE	100

typedef struct s_render_context
{
	float		*z_buffer;
	t_game		*game;
	t_img_data	*frame;
	t_player	*player;
	t_tilemap	*tilemap;
	t_vec2		position;
	int			render_width;
	int			render_height;
	float		fov;
	float		fov_y;
	float		yaw_cos;
	float		yaw_sin;
	float		proj_dist_x;
	float		proj_dist_y;
	float		focal;
	int			halfh;
	int			halfw;
	float		eye_height;
	float		direction;
	float		aspect_res;
	float		ratio;
	t_png		**textures;
}	t_render_context;

typedef struct s_raycast_hit
{
	bool		draw_walls;
	t_vec2		pos;
	t_ray2		o_ray;
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
	float				last_floor;
	float				last_ceil;
}	t_raycast_context;

typedef struct s_vertical_tex
{
	int		x;
	int		y;
	int		side;
	t_png	*texture;
	int		wall_start;
	int		wall_start_actual;
	int		wall_end;
	int		wall_end_actual;
	int		wall_height;
	int		tex_x;
}	t_vertical_tex;

void	render_ray(float base_angle, int column,
			t_ray2 *ray, t_render_context *render_ctx);
void	render_draw_ray(t_raycast_hit *hit, t_raycast_context *ctx,
			t_render_context *render);
void	manage_texture(t_raycast_hit *hit, t_raycast_context *ctx,
			t_render_context *render, t_vertical_tex	*tex_ctx);
void	render_horizontal_texture(t_ivec2 pixel, t_vec2 real_pos,
			t_render_context *r_ctx, t_texture_type texture_type);

#endif
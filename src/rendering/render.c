/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:50:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/02 13:52:18 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <immintrin.h>
#include "cub3d.h"
#include "cub3d_rendering.h"

static inline void	render_rays(int start, int end, t_render_context *render);
static void		render_init(int width, int height, \
	t_render_context *context, t_game *game);

void	render(t_game *game)
{
	t_render_context	context;

	render_init(WINDOW_WIDTH, WINDOW_HEIGHT, &context, game);
	render_rays(0, context.render_width, &context);
	draw_minimap(game);
	draw_enemies(game);
	manage_pnjs(game);
	if (is_key_pressed(KEY_TAB, game))
		draw_full_map(game);
}

static void	render_init(int width, int height,
		t_render_context *context, t_game *game)
{
	static uint8_t	z_buffer[WINDOW_WIDTH * WINDOW_HEIGHT] = {UINT8_MAX};

	ft_memset(z_buffer, UINT8_MAX, sizeof(z_buffer));
	context->z_buffer = &z_buffer[0];
	context->game = game;
	context->tilemap = game->tilemap;
	context->frame = game->img;
	context->player = &game->player;
	context->position = game->player.position;
	context->direction = game->player.rad_direction;
	context->render_height = height;
	context->render_width = width;
	context->eye_height = game->player.height;
	context->fov = deg_to_rad(game->player.fov_deg);
	context->fov_x = context->fov;
	context->fov_y = deg_to_rad(game->player.fov_deg - 15);
	context->halfw = WINDOW_WIDTH * .5f;
	context->halfh = WINDOW_HEIGHT * .5f;
	context->proj_dist_x = context->halfw / tanf(context->fov_x * .5f);
	context->proj_dist_y = context->halfh / tanf(context->fov_y * .5f);
}

static inline void	render_rays(int start, int end, t_render_context *render)
{
	t_ray2			ray;
	int				x;
	float			camera_x;
	float			ray_angle;

	x = start;
	while (x < end)
	{
		camera_x = 2.0 * x / (float)WINDOW_WIDTH - 1.0;
		ray_angle = render->direction + atan(camera_x * tan(render->fov / 2));
		ray = ray2_from_angle(render->position, ray_angle);
		render_ray(ray_angle, x, &ray, render);
		x++;
	}
}

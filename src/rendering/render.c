/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:50:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/16 12:26:56 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static void	render_init(int width, int height, t_render_context *context, t_game *game);

void	render(t_game *game)
{
	t_render_context	context;

	render_init(WINDOW_WIDTH, WINDOW_HEIGHT, &context, game);
	render_rays(0, context.render_width, &context);
	draw_minimap(game);
	handle_full_map(game);
}

static void	render_init(int width, int height, t_render_context *context, t_game *game)
{
	context->game = game;
	context->frame = game->img;
	context->player = &game->player;
	context->position = game->player.position;
	context->direction = game->player.rad_direction;
	context->render_height = height;
	context->render_width = width;
	context->fov = deg_to_rad(game->player.fov_deg);
}

static void render_ray(float ray_angle, int collumn,
		t_raycast_hit *result, t_render_context *context);

void	render_rays(int start_x, int end_x, t_render_context *render)
{
	t_ray2			ray;
	t_raycast_hit	ray_result;
	int				x;
	float			camera_x;
	float			ray_angle;

	x = start_x;
	while (x < end_x)
	{
		camera_x = 2.0 * x / (float)WINDOW_WIDTH - 1.0;
		ray_angle = render->direction + atan(camera_x * tan(render->fov / 2));
		ray = ray2_from_angle(render->position, ray_angle);
		ray_result = raycast_tilemap(&ray, render->game->tilemap);
		render_ray(ray_angle, x, &ray_result, render);
		x++;
	}
}

static void render_ray(float ray_angle, int collumn,
		t_raycast_hit *result, t_render_context *context)
{
	float	corrected_dist;
	int		wall_height;
	int		wall_start;
	int		wall_end;
	int		y;

	corrected_dist = result->dist * cosf(ray_angle - context->direction);
	wall_height = WINDOW_HEIGHT / corrected_dist;
	wall_start = clamp(-wall_height / 2 + WINDOW_HEIGHT / 2, 0, WINDOW_HEIGHT);
	wall_end = clamp(wall_height / 2 + WINDOW_HEIGHT / 2, 0, WINDOW_HEIGHT);
	result->pos.x = result->original_ray.origin.x + result->original_ray.dir_normal.x * corrected_dist;
	result->pos.y = result->original_ray.origin.y + result->original_ray.dir_normal.y * corrected_dist;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < wall_start)
			img_draw_pixel(rgba8(0, 0, 255, 255), collumn, y, context->frame);
		else if (y > wall_end)
			img_draw_pixel(rgba8(0, 255, 255, 255), collumn, y, context->frame);
		else
			render_texture(result, context, collumn, &y, wall_end, wall_height);
		y++;
	}
}

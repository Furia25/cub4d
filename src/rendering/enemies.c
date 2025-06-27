/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:11:48 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/27 10:48:57 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calculate_distance(t_vec2 p_pos, t_vec2 e_pos, t_vec2 axis_dist)
{
	float	dist;
	float	squared;

	if (p_pos.x == e_pos.x)
		return (axis_dist.y);
	else if (p_pos.y == e_pos.y)
		return (axis_dist.x);
	else
	{
		squared = (axis_dist.y * axis_dist.y) + (axis_dist.x * axis_dist.x);
		dist = sqrt(squared);
		return (dist);
	}
}

t_vec2	calculate_axis_dist(t_vec2 p_pos, t_vec2 e_pos)
{
	t_vec2	axis_dist;

	if (p_pos.y > e_pos.y)
		axis_dist.y = p_pos.y - e_pos.y;
	else
		axis_dist.y = e_pos.y - p_pos.y;
	if (p_pos.x > e_pos.x)
		axis_dist.x = p_pos.x - e_pos.x;
	else
		axis_dist.x = e_pos.x - p_pos.x;
	return (axis_dist);
}


static void render_enemy(t_game *game, float dist, t_vec2 pos)
{
	t_png	*sprite;
	int		sprite_size;
	int		start_x;
	int		start_y;
	int		screen_y;
	int 	screen_x;
	int 	tex_x;
	int 	tex_y;
	int 	y;
	int 	x;

	sprite = game->sprites[SPRITE_ENEMY];
	sprite_size = (int)(sprite->header.height / dist);
	if (sprite_size <= 0)
		return ;
	start_x = pos.x - sprite_size / 2;
	start_y = pos.y - sprite_size / 2;
	y = 0;
	while (y < sprite_size)
	{
		screen_y = start_y + y;
		if (screen_y < 0 || screen_y >= WINDOW_HEIGHT)
		{
			y++;
			continue ;
		}
		tex_y = (y * sprite->header.height) / sprite_size;
		x = 0;
		while (x < sprite_size)
		{
			screen_x = start_x + x;
			if (screen_x < 0 || screen_x >= WINDOW_WIDTH)
			{
				x++;
				continue ;
			}
			tex_x = (x * sprite->header.width) / sprite_size;
			draw_pixel(sprite->pixels_8bit[tex_y * sprite->header.width + tex_x], screen_x, screen_y, game->img);
			x++;
		}
		y++;
	}
}

// static t_vec2	calculate_position(t_vec2 p_pos, float direction, t_vec2 e_pos)
// {
// 	t_vec2	axis_vect;
// }

static void	draw_enemy(t_game *game, t_enemy enemy, t_vec2 pos)
{
	float	dist;
	t_vec2	axis_dist;

	axis_dist = calculate_axis_dist(game->player.position, enemy.position);
	dist = calculate_distance(game->player.position, enemy.position, axis_dist);
	// printf("dist:%f\n", dist);
	// pos = calculate_position(game->player.position, game->player.rad_direction, enemy.position);
	render_enemy(game, dist, pos);
}

void	draw_enemies(t_game *game)
{
	int	i;
	t_vec2	pos;

	pos.x = WINDOW_HEIGHT / 2;
	pos.y = 400;
	i = 0;
	while (i < game->enemy_count)
	{
		draw_enemy(game, game->enemies[i], pos);
		pos.x += 1200;
		i++;
	}
}

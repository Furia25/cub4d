/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:11:48 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/21 01:03:54 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*static float	calculate_distance(t_vec2 p_pos, t_vec2 e_pos, t_vec2 axis_dist)
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

static t_vec2	calculate_axis_dist(t_vec2 p_pos, t_vec2 e_pos)
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

// static t_vec2	calculate_position(t_vec2 p_pos, float direction, t_vec2 e_pos)
// {
// 	t_vec2	axis_vect;

	  
static void	draw_enemy(t_game *game, t_enemy enemy)
{
	float	dist;
	t_vec2	axis_dist;

	axis_dist = calculate_axis_dist(game->player.position, enemy.position);
	dist = calculate_distance(game->player.position, enemy.position, axis_dist);
	// pos = calculate_position(game->player.position, game->player.rad_direction, enemy.position);
}*/

void	draw_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		i++;
	}
}

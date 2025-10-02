/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:02:44 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/01 10:06:45 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

int	calculate_offset(double p_pos)
{
	int		offset;
	double	diff;

	diff = p_pos - floor(p_pos);
	offset = (int)(MMAP_TILE_SIZE * diff);
	return (offset);
}

void	init_tile_ctx(t_game *game, t_vec3 pos, t_tile_context *tile_info)
{
	int				off_x;
	int				off_y;
	float			ent_off_x;
	float			ent_off_y;
	t_vec2			minimap_pos;

	off_x = calculate_offset(game->player.position.x);
	off_y = calculate_offset(game->player.position.y);
	ent_off_x = pos.x - floor(pos.x);
	ent_off_y = pos.x - floor(pos.x);
	pos.x = floor(pos.x);
	pos.y = floor(pos.y);
	minimap_pos.x = 8 - game->player.position.x + pos.x;
	minimap_pos.y = 8 - game->player.position.y + pos.y;
	*tile_info = (t_tile_context){game, NULL, 0, floor(minimap_pos.x),
		floor(minimap_pos.y), off_x, off_y, ent_off_x, ent_off_y};
}

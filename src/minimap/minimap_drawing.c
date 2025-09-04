/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:49:50 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/04 16:00:22 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

void	draw_tile(t_tile_context *tile, t_rgba8 color, int mid_off)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < MMAP_TILE_SIZE - mid_off)
	{
		j = 0;
		while (j < MMAP_TILE_SIZE - mid_off)
		{
			x = (tile->pos_x * MMAP_TILE_SIZE + i - tile->off_x \
				+ MINIMAP_X_START + MINIMAP_BORDER) + (mid_off / 2);
			y = (tile->pos_y * MMAP_TILE_SIZE + j - tile->off_y \
				+ MINIMAP_Y_START + MINIMAP_BORDER) + (mid_off / 2);
			if (x >= MINIMAP_X_START + MINIMAP_BORDER && \
				x < MINIMAP_X_START + MINIMAP_SIZE && \
				y >= MINIMAP_Y_START + MINIMAP_BORDER && \
				y < MINIMAP_Y_START + MINIMAP_SIZE)
				draw_pixel(color, x, y, tile->game->frame);
			j++;
		}
		i++;
	}
}

void	draw_border(t_game *game)
{
	int				i;
	int				j;
	t_rgba8			color;

	color = rgba8(25, 255, 25, 200);
	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			if (j < MINIMAP_BORDER || \
				j > MINIMAP_SIZE - MINIMAP_BORDER || \
				i < MINIMAP_BORDER || \
				i > MINIMAP_SIZE - MINIMAP_BORDER)
			{
				draw_pixel(color, i + MINIMAP_X_START,
					j + MINIMAP_Y_START, game->frame);
			}
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_P_SIZE)
	{
		j = 0;
		while (j < MINIMAP_P_SIZE)
		{
			draw_pixel(
				rgba8(255, 0, 10, 200),
				((7 * MMAP_TILE_SIZE) + i + MINIMAP_X_START \
				+ MINIMAP_BORDER - (MINIMAP_P_SIZE / 2)),
				((7 * MMAP_TILE_SIZE) + j + MINIMAP_Y_START \
				+ MINIMAP_BORDER - (MINIMAP_P_SIZE / 2)),
				game->frame
				);
			j++;
		}
		i++;
	}
}

void	draw_entities(t_game *game)
{
	int				i;
	int				off_x;
	int				off_y;
	int				pos_x;
	int				pos_y;
	t_vector		*entities;
	t_entity		*entity;
	t_vec3			pos;
	t_tile_context	tile_info;

	i = 0;
	entities = game->entity_manager.entities;
	while (entity != NULL)
	{
		entity = entities->items[i];
		if (entity)
		{
			pos = entity->position;
			if ((pos.x >= game->player.position.x - 8 \
				&& pos.x <= game->player.position.x + 9) \
				&& (pos.y >= game->player.position.y - 8 \
				&& pos.y <= game->player.position.y + 9))
			{
				off_x = calculate_offset(game->player.position.x);
				off_y = calculate_offset(game->player.position.y);
				pos_x = 8 - game->player.position.x + pos.x;
				pos_y = 8 - game->player.position.y + pos.y;
				printf("off_x:%d, off_y:%d\n", off_x, off_y);
				tile_info = (t_tile_context){game, NULL, 0, pos_x, pos_y, off_x, off_y};
				draw_tile(&tile_info, entity->transform.color, MMAP_TILE_SIZE / 2);
			}
		}
		i++;
	}
}
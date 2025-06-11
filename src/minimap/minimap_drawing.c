/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:49:50 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/11 11:54:26 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_tile_context *tile, t_png_pixel8 color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < MMAP_TILE_SIZE)
	{
		j = 0;
		while (j < MMAP_TILE_SIZE)
		{
			x = (tile->pos_x * MMAP_TILE_SIZE + i - tile->off_x \
				+ MINIMAP_X_START + MINIMAP_BORDER);
			y = (tile->pos_y * MMAP_TILE_SIZE + j - tile->off_y \
				+ MINIMAP_Y_START + MINIMAP_BORDER);
			if (x >= MINIMAP_X_START + MINIMAP_BORDER && \
				x < MINIMAP_X_START + MINIMAP_SIZE && \
				y >= MINIMAP_Y_START + MINIMAP_BORDER && \
				y < MINIMAP_Y_START + MINIMAP_SIZE)
				img_draw_pixel(color, x, y, tile->game->img);
			j++;
		}
		i++;
	}
}

void	draw_border(t_game *game)
{
	int				i;
	int				j;
	t_png_pixel8	color;

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
				img_draw_pixel(color, i + MINIMAP_X_START,
					j + MINIMAP_Y_START, game->img);
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
			img_draw_pixel(
				rgba8(255, 0, 10, 200),
				((7 * MMAP_TILE_SIZE) + i + MINIMAP_X_START \
				+ MINIMAP_BORDER - (MINIMAP_P_SIZE / 2)),
				((7 * MMAP_TILE_SIZE) + j + MINIMAP_Y_START \
				+ MINIMAP_BORDER - (MINIMAP_P_SIZE / 2)),
				game->img
				);
			j++;
		}
		i++;
	}
}
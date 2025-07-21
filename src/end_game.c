/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:09:37 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/21 13:32:19 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"

int	exit_game(t_game *game)
{
	int i;

	i = 0;
	while (i < game->pnj_count)
	{
		free_map(game->pnjs[i].text);
		i++;
	}
	tilemap_free(game->tilemap);
	free(game->paths);
	free(game->colors);
	free(game->map);
	free_map(game->file_content);
	free_map(game->pnj_text);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->img)
	{
		if (game->img->img_ptr)
			mlx_destroy_image(game->mlx, game->img->img_ptr);
		free(game->img);
	}
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	png_close(game->textures[TEXTURE_NORTH]);
	png_close(game->textures[TEXTURE_WEST]);
	png_close(game->textures[TEXTURE_EAST]);
	png_close(game->textures[TEXTURE_SOUTH]);
	png_close(game->textures[TEXTURE_TOP]);
	png_close(game->textures[TEXTURE_BOT]);
	png_close(game->menu.assets[ASSET_SELECTOR]);
	png_close(game->menu.assets[ASSET_BG_PAUSE]);
	png_close(game->menu.assets[ASSET_BG_START]);
	glyph_end();
	free(game->mlx);
	exit(EXIT_SUCCESS);
}

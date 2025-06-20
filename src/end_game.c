/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:09:37 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/20 15:58:48 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(t_game *game)
{
	tilemap_free(game->tilemap);
	free(game->paths);
	free(game->colors);
	free(game->map);
	free_map(game->file_content);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->img)
	{
		if (game->img->img_ptr)
			mlx_destroy_image(game->mlx, game->img->img_ptr);
		free(game->img);
	}
	mlx_destroy_display(game->mlx);
	png_close(game->textures[TEXTURE_NORTH]);
	png_close(game->textures[TEXTURE_WEST]);
	png_close(game->textures[TEXTURE_EAST]);
	png_close(game->textures[TEXTURE_SOUTH]);
	png_close(game->sprites[SPRITE_ENEMY]);
	free(game->mlx);
	exit(EXIT_SUCCESS);
}

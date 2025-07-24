/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:09:37 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/24 20:29:22 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"

static void	free_textures(t_game *game);

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
	if (game->frame)
	{
		if (game->frame->img_ptr)
			mlx_destroy_image(game->mlx, game->frame->img_ptr);
		free(game->frame);
	}
	free(game->z_buffer);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free_textures(game);
	glyph_end();
	free(game->mlx);
	exit(EXIT_SUCCESS);
}

static void	free_textures(t_game *game)
{
	t_png	*ptr;
	t_png	*missing_ptr;
	int		index;

	index = 1;
	missing_ptr = game->textures[TEXTURE_ERROR];
	while (index < TEXTURE_MAX_COUNT)
	{
		ptr = game->textures[index];
		if (ptr != missing_ptr && ptr)
			png_close(ptr);
		index++;
	}
	png_close(missing_ptr);
}

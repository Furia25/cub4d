/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:09:37 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/05 18:36:36 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"
#include "cub3d_errors.h"

static void	free_textures(t_game *game);

int	exit_game(t_game *game)
{
	if (game->parsing.file_fd != -1)
		close(game->parsing.file_fd);
	game->textures[TEXTURE_WATER] = NULL;
	tilemap_free(game->tilemap);
	property_inputs_free(&game->parsing.temp_inputs);
	free_tab((void **)game->parsing.map);
	free_tab((void **)game->parsing.file_content);
	if (game->win.ptr)
		mlx_destroy_window(game->mlx, game->win.ptr);
	if (game->frame)
	{
		if (game->frame->img_ptr)
			mlx_destroy_image(game->mlx, game->frame->img_ptr);
		free(game->frame);
	}
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game->z_buffer);
	free_textures(game);
	vector_free(game->events_postload, true);
	vector_free(game->entity_manager.entities, true);
	ft_putchar_fd('\n', 1);
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
	free(game->parsing.textures_paths[0]);
	free(game->parsing.textures_paths[1]);
	free(game->parsing.textures_paths[2]);
	free(game->parsing.textures_paths[3]);
	glyph_end();
}

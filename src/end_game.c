/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:09:37 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/26 16:27:00 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"
#include "cub3d_errors.h"

static const char	*g_errors[ERROR_MAX] = {
[ERROR_ALLOC] = "Couldn't allocate enough memory.",
[ERROR_PARSING] = "Unable to continue the map parsing.",
[ERROR_PARSING_IO] = "Unable to open/read the map file.",
[ERROR_PARSING_VALIDITY] = "Map couldn't be used, verify integrity.",
[ERROR_LOADING_ASSETS] = "Couldn't load assets.",
[ERROR_LOADING_GRAPHICS] = "Couldn't load textures.",
[ERROR_LOADING] = "Initilization of the game failed.",
[ERROR_WINDOW] = "Unable to create Window and/or Framebuffers.",
[ERROR_ENTITIES_ALLOC] = "Entities Manager caused a memory allocation error.",
[ERROR_ENTITIES_MISC] = "Unexpected entity manager error.",
[ERROR_ENTITIES_INVALID] = "Entity Manager couldn't resolve unknown entity."
};

void	throw_error(t_game *game, t_error error)
{
	ft_putstr_fd(GAME_NAME, 2);
	ft_putstr_fd(" : ", 2);
	if (error < ERROR_MAX)
		ft_putstr_fd((char *)g_errors[error], 2);
	else
		ft_putstr_fd(ERROR_BASIC, 2);
	ft_putstr_fd("\n", 2);
	exit_game(game);
}

static void	free_textures(t_game *game);

int	exit_game(t_game *game)
{
	if (game->parsing.file_fd != -1)
		close(game->parsing.file_fd);
	game->textures[TEXTURE_WATER] = NULL;
	tilemap_free(game->tilemap);
	free(game->sky_buffer);
	free(game->parsing.paths);
	free(game->parsing.colors);
	free(game->parsing.map);
	free_map(game->parsing.file_content);
	if (game->win.ptr)
		mlx_destroy_window(game->mlx, game->win.ptr);
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
	free(game->mlx);
	vector_free(game->entity_manager.entities, true);
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
	glyph_end();
}

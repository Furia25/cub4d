/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:09:37 by halnuma           #+#    #+#             */
/*   Updated: 2025/08/20 18:39:43 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"
#include "cub3d_errors.h"

static const char	*g_errors[ERROR_MAX] = {
[ERROR_LOADING_ASSETS] = "Couldn't load assets.",
[ERROR_LOADING_GRAPHICS] = "Couldn't load textures.",
[ERROR_LOADING] = "Initilization of the game failed.",
[ERROR_WINDOW] = "Unable to create Window and/or Frame buffer."
};

void	trow_error(t_game *game, t_error error)
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
	tilemap_free(game->tilemap);
	free(game->paths);
	free(game->colors);
	free(game->map);
	free_map(game->file_content);
	free_map(game->npc_text);
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
}

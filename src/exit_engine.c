/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:09:37 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/01 00:27:57 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"
#include "cub3d_errors.h"

const char	*g_errors[ERROR_MAX] = {
[ERROR_ALLOC] = "Couldn't allocate enough memory.",
[ERROR_PARSING] = "Unable to continue the map parsing.",
[ERROR_PARSING_IO] = "Unable to open/read the map file.",
[ERROR_PARSING_VALIDITY] = "Map couldn't be used, verify integrity.",
[ERROR_PARSING_NL_MAP] = "Unexpected new line in tilemap.",
[ERROR_PARSING_ALLOC] = "Couldn't allocate enough memory when parsing.",
[ERROR_PARSING_PLAYERS] = "Map must contain exactly one player spawn point.",
[ERROR_PARSING_NOPLAYER] = "Map must contain at least one player spawn point.",
[ERROR_PARSING_SYMBOL] = "Invalid map tile symbol encountered.",
[ERROR_PARSING_PROPERTY] = "Malformed property: check map integrity",
[ERROR_PROPERTY_COLOR] = "Malformed property: 'C|F' <red:byte> <green:byte> \
<blue:byte>\n 'A' <red:byte> <green:byte> <blue:byte> [intensity:0-250]",
[ERROR_PROPERTY_ENTITY_UNKNOWN] = "Malformed property: Unknown entity type",
[ERROR_PROPERTY_ENTITY] = "Malformed property: 'ENTITY' <type:string> <x:float> \
 <y:float> <z:float> [optional_datas]",
[ERROR_PROPERTY_PATH] = "Malformed property: 'EA|WE|SO|NO' <path:string>",
[ERROR_PARSING_BROADCAST] = "Malformed property: '##' <broadcast:string>",
[ERROR_PARSING_UNCLOSED] = "All tiles must be surrounded by walls; \
the map cannot have open edges.",
[ERROR_PARSING_MISSING_COLOR] = "Invalid map configuration: floor and \
ceiling colors must be defined using the F and C properties.",
[ERROR_PARSING_MISSING_PATHS] = "Invalid map configuration: wall textures \
must be defined for all directions using the NO, SO, WE, and EA properties.",
[ERROR_LOADING_ASSETS] = "Couldn't load assets.",
[ERROR_LOADING_TEXTURES_FALLBACK] = "Failed to load fallback error texture \
from the required path",
[ERROR_LOADING_TEXTURES_FATAL] = "Fatal error occurred while loading textures",
[ERROR_LOADING_GLYPHS] = "Failed to load or initialize glyphs.",
[ERROR_LOADING_GRAPHICS] = "Couldn't load textures.",
[ERROR_LOADING] = "Initilization of the game failed.",
[ERROR_WINDOW] = "Unable to create Window and/or Framebuffers.",
[ERROR_ENTITIES_ALLOC] = "Entities Manager caused a memory allocation error.",
[ERROR_ENTITIES_MISC] = "Unexpected entity manager error.",
[ERROR_ENTITIES_INVALID] = "Entity Manager couldn't resolve unknown entity.",
[ERROR_ENTITY_NPC] = "Malformed Entity Data: 'NPC' [text:string]",
[ERROR_WTF] = "You are cooked, I don't even know how it's possible."
};

void	throw_error(t_game *game, t_error error)
{
	throw_error_info(game, error, NULL);
}

void	throw_error_info(t_game *game, t_error error, char *info)
{
	ft_putstr_fd(ERROR_PREFIX, 2);
	if (error < ERROR_MAX)
		ft_putstr_fd((char *)g_errors[error], 2);
	else
		ft_putstr_fd(ERROR_BASIC, 2);
	if (info)
	{
		ft_putstr_fd(": \"", 2);
		ft_putstr_fd(info, 2);
		ft_putchar_fd('\"', 2);
	}
	ft_putstr_fd("\n", 2);
	exit_game(game);
}

void	player_death(t_game *game)
{
	printf(ANSI_BOLD ANSI_RED DEATH_MESSAGE ANSI_RESET);
	exit_game(game);
}

static void	free_textures(t_game *game);

int	exit_game(t_game *game)
{
	if (game->parsing.file_fd != -1)
		close(game->parsing.file_fd);
	game->textures[TEXTURE_WATER] = NULL;
	tilemap_free(game->tilemap);
	free(game->level_broadcast);
	free_tab((void **)game->parsing.temp_prop.argv);
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

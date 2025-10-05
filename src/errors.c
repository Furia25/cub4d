/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:55:28 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 00:52:47 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"

const char	*g_errors[ERROR_MAX] = {
[ERROR_NONE] = "",
[ERROR_BASIC] = "Unexpected error.",
[ERROR_ALLOC] = "Couldn't allocate enough memory.",
[ERROR_PARSING] = "Unable to continue the map parsing.",
[ERROR_PARSING_IO] = "Unable to open/read the map file.",
[ERROR_PARSING_VALIDITY] = "Map couldn't be used, verify integrity.",
[ERROR_PARSING_NL_MAP] = "Unexpected new line in tilemap.",
[ERROR_PARSING_QUOTE] = "Unclosed quote",
[ERROR_PARSING_ALLOC] = "Couldn't allocate enough memory when parsing.",
[ERROR_PARSING_PLAYERS] = "Map must contain exactly one player spawn point.",
[ERROR_PARSING_NOPLAYER] = "Map must contain at least one player spawn point.",
[ERROR_PARSING_SYMBOL] = "Invalid map tile symbol encountered.",
[ERROR_PARSING_PROPERTY] = "Malformed property: check map integrity",
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
[ERROR_WTF] = "You are cooked, I don't even know how it's possible.",
[ERROR_PROP_TOOMANY] = "Too many arguments/values for this property",
[ERROR_PROP_MISSING] = "Required property is missing",
[ERROR_PROP_DUPLICATE] = "Property defined multiple times",
[ERROR_PROP_UNCLOSED_QUOTE] = "Unclosed quote",
[ERROR_PROP_UNCLOSED_STRUCT] = "Unclosed struct",
[ERROR_PROP_UNCLOSED_ARRAY] = "Unclosed array",
[ERROR_PROP_INVALID] = "Invalid Values",
[ERROR_PROP_UNKNOWN] = "Unknown property"
};

void	print_error(bool newline, t_error error, t_game *game)
{
	if (error != ERROR_NONE)
	{
		ft_putstr_fd(ERROR_PREFIX, 2);
		if (error < ERROR_MAX)
			ft_putstr_fd((char *)g_errors[error], 2);
	}
	if (newline)
		ft_putstr_fd("\n", 2);
}

void	throw_error_info(t_error error, char *info, t_game *game)
{
	print_error(false, game, error);
	if (info && info[0])
		ft_printf_fd(2, ": %s", info);
	ft_putstr_fd("\n", 2);
	exit_game(game);
}

void	throw_error(t_error error, t_game *game)
{
	print_error(true, error, game);
	exit_game(game);
}

void	print_error_property(bool newline, t_property *prop,
			t_error error, int line)
{
	ft_printf_fd(2, "Error: Line %d: Property '%s' — %s\n",
		line, prop->name, g_errors[error]);
}

void	throw_error_property(const t_property *prop,
			t_error error, t_game *game)
{
	if (!prop)
		throw_error(ERROR_BASIC, game);
	if (error != ERROR_NONE)
		print_error_property(true, prop, error, game->parsing.line_num);
	print_property_usage(prop);
	exit_game(game);
}

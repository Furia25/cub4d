/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:33:43 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/29 19:11:23 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ERRORS_H
# define CUB3D_ERRORS_H

# define WARNING_PREFIX	"\033[33mWarning:\033[0m "
# define ERROR_PREFIX	"\033[31m\033[1mError:\033[0m "
# define ERROR_BASIC	"Unexpected error: game has crashed."

typedef enum e_error
{
	ERROR_ALLOC,
	ERROR_PARSING,
	ERROR_PARSING_ALLOC,
	ERROR_PARSING_IO,
	ERROR_PARSING_VALIDITY,
	ERROR_PARSING_NL_MAP,
	ERROR_PARSING_PLAYERS,
	ERROR_PARSING_NOPLAYER,
	ERROR_PARSING_PROPERTY,
	ERROR_PARSING_MISSING_COLOR,
	ERROR_PARSING_MISSING_PATHS,
	ERROR_PARSING_UNCLOSED,
	ERROR_PARSING_SYMBOL,
	ERROR_LOADING_ASSETS,
	ERROR_LOADING_TEXTURES_FALLBACK,
	ERROR_LOADING_TEXTURES_FATAL,
	ERROR_LOADING_GRAPHICS,
	ERROR_LOADING_GLYPHS,
	ERROR_LOADING,
	ERROR_WINDOW,
	ERROR_ENTITIES_ALLOC,
	ERROR_ENTITIES_MISC,
	ERROR_ENTITIES_INVALID,
	ERROR_WTF,
	ERROR_MAX
}	t_error;

extern const char	*g_errors[ERROR_MAX];

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:33:43 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/27 16:40:10 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ERRORS_H
# define CUB3D_ERRORS_H

# define ERROR_BASIC	"Unexpected error: game has crashed."

typedef enum e_error
{
	ERROR_ALLOC,
	ERROR_PARSING,
	ERROR_PARSING_ALLOC,
	ERROR_PARSING_IO,
	ERROR_PARSING_VALIDITY,
	ERROR_PARSING_NL_MAP,
	ERROR_PARSING_PLAYER,
	ERROR_PARSING_PROPERTY,
	ERROR_PARSING_MISSING_COLOR,
	ERROR_PARSING_UNCLOSED,
	ERROR_PARSING_SYMBOL,
	ERROR_LOADING_ASSETS,
	ERROR_LOADING_GRAPHICS,
	ERROR_LOADING,
	ERROR_WINDOW,
	ERROR_ENTITIES_ALLOC,
	ERROR_ENTITIES_MISC,
	ERROR_ENTITIES_INVALID,
	ERROR_WTF,
	ERROR_MAX
}	t_error;

#endif
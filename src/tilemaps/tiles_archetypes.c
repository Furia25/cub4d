/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_archetypes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:54:59 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/29 19:19:22 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_symbol_player(char c)
{
	return (c == SYMBOL_PLAYER_NORTH || c == SYMBOL_PLAYER_SOUTH
		|| c == SYMBOL_PLAYER_EAST || c == SYMBOL_PLAYER_WEST);
}

bool	is_symbol_border(char c)
{
	return (c == SYMBOL_WALL);
}

bool	is_symbol_central(char c)
{
	return (is_symbol_valid(c) && !is_symbol_border(c) && c != ' ');
}

bool	is_symbol_valid(char c)
{
	return (c == SYMBOL_WATER || c == SYMBOL_WALL || c == SYMBOL_GRASS
		|| is_symbol_player(c) || c == ' ');
}

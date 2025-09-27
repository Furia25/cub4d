/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:07:02 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/27 02:21:07 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_symbol_player(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

bool	is_symbol_border(char c)
{
	return (c == '1');
}

bool	is_symbol_central(char c)
{
	return (is_symbol_valid(c) && !is_symbol_border(c)
		&& c != ' ' && c != '\n');
}

bool	is_symbol_valid(char c)
{
	return (c == '0' || c == '1' || c == '2'
		|| is_symbol_player(c) || c == '\n' || c == ' ');
}

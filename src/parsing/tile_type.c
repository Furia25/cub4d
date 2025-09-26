/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:55:18 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/26 18:41:42 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_tile(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_center_tile(char c)
{
	return (check_tile_validity(c) && !is_wrapping_tile(c));
}

int	is_wrapping_tile(char c)
{
	return (c == '1');
}

int	check_tile_validity(char c)
{
	if (c != '1' && c != '2' && c != '0' && c != 'N' && c != 'E' && \
		c != 'S' && c != 'W' && c != 'P' && c != ' ' && c != '\n')
		return (0);
	return (1);
}

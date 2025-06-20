/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:55:18 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/20 10:47:26 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_tile(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	return (1);
}

int	center_tile(char c)
{
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && \
		c != 'P')
		return (0);
	return (1);
}

int	wrapping_tile(char c)
{
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && \
		c != '1' && c != 'P')
		return (0);
	return (1);
}

int	check_tile_validity(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'E' && \
		c != 'S' && c != 'W' && c != 'P' && c != ' ' && c != '\n')
		return (0);
	return (1);
}

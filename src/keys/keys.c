/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:51:19 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/04 18:04:53 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	key_check(t_key_type type, t_game *game)
{
	return (game->key_buffer[type].pressed);
}

bool	key_is_released(t_key_type type, t_game *game)
{
	if (game->key_buffer[type].released_once)
	{
		game->key_buffer[type].released_once = false;
		return (true);
	}
	return (false);
}

bool	key_is_pressed(t_key_type type, t_game *game)
{
	if (game->key_buffer[type].pressed_once)
	{
		game->key_buffer[type].pressed_once = false;
		return (true);
	}
	return (false);
}

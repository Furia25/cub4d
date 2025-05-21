/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:10:34 by halnuma           #+#    #+#             */
/*   Updated: 2025/05/21 11:10:49 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int key_pressed, void *param)
{
	t_game	*game;

	game = param;
	if (key_pressed == ESCAPE)
		exit_game(game);
	return (1);
}

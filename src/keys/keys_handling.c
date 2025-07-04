/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:29:22 by val               #+#    #+#             */
/*   Updated: 2025/07/04 18:22:17 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_keys(t_game *game)
{
	size_t	index;

	index = 0;
	while (index < KEY_MAX_COUNT)
	{
		if (index == KEY_MAX_COUNT - 1)
			printf("%d", game->key_buffer[index].pressed);
		else
			printf("%d ,", game->key_buffer[index].pressed);
		index++;
	}
	printf("\n");
}

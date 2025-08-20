/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:27:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/20 18:40:12 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"

void	entity_free(t_entity *entity)
{
	if (entity->free_data)
		entity->free_data(entity->data);
	free(entity);
}

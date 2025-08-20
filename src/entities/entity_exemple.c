/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_exemple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:33:23 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/21 01:31:02 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"

/*Entity constructor*/

t_entity	*entity_new_example(t_vec3 position, t_game *game)
{
	t_entity	*entity;

	entity = ft_calloc(1, sizeof(t_entity));
	if (!entity)
		trow_error(game, ERROR_ENTITIES_MISC);
	entity_init_basics(position, entity);
	return (entity);
}

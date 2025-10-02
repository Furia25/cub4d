/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   property_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 03:02:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 03:04:32 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

static inline void	build_entity(char *line, t_property prop, t_game *game);

void	parse_property_entity(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	parsing->temp_prop = property_get_args(line, type, game);
	if (!parsing->temp_prop.argv)
		throw_error(game, ERROR_PARSING_ALLOC);
	if (parsing->temp_prop.argc < 4)
		throw_error_info(game, ERROR_PROPERTY_ENTITY, line);
	build_entity(line, parsing->temp_prop, game);
}

static inline const t_entity_ctx	*get_constructors(char *token);

static inline void	build_entity(char *line, t_property prop, t_game *game)
{
	const t_entity_ctx		*data = get_constructors(prop.argv[0]);
	t_entity				*entity;
	t_vec3					pos;

	if (!data || !data->constructor)
		throw_error_info(game, ERROR_PROPERTY_ENTITY_UNKNOWN, line);
	pos = (t_vec3){ft_atof(prop.argv[1]),
		ft_atof(prop.argv[2]), ft_atof(prop.argv[3])};
	entity = data->constructor(pos, game);
	if (!entity)
		throw_error(game, ERROR_ENTITIES_ALLOC);
	if (data->data_constructor && data->data_constructor(entity,
			(t_property){prop.argv + 4, prop.argc - 4}, game) == false)
	{
		entity_free(entity);
		throw_error_info(game, data->error, line);
	}
	entity_add(entity, game);
}

/*Function to get constructors from token, 
for each entities token add an entry into the factory array*/

static inline const t_entity_ctx	*get_constructors(char *token)
{
	size_t						index;
	static const t_entity_ctx	factory[] = {
	{"NPC", entity_new_npc, entity_npc_data, ERROR_ENTITY_NPC},
	{"TREE", entity_new_tree, NULL, ERROR_ALLOC},
	{NULL, NULL, NULL, 0}};

	index = 0;
	while (factory[index].constructor != NULL)
	{
		if (ft_strcmp(token, factory[index].token) == 0)
			return (&factory[index]);
		index++;
	}
	return (NULL);
}

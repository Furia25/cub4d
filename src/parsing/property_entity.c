/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   property_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 03:02:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/30 19:07:57 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

void	parse_property_entity(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	t_property				*prop;

	parsing->temp_prop = property_get_args(line, type, game);
	if (!parsing->temp_prop.argv)
		throw_error(game, ERROR_PARSING_ALLOC);
	if (parsing->temp_prop.argc < 4)
		throw_error_info(game, ERROR_PROPERTY_ENTITY, line);
	prop = malloc(sizeof(t_property));
	if (!prop)
		throw_error(game, ERROR_PARSING_ALLOC);
	prop->argv = parsing->temp_prop.argv;
	prop->argc = parsing->temp_prop.argc;
	if (!vector_append(parsing->entities_cache, prop))
	{
		free(prop);
		throw_error(game, ERROR_PARSING_ALLOC);
	}
	parsing->temp_prop.argv = NULL;
}

static inline void	build_entity(t_property *prop, t_game *game);

void	build_entities(t_parsing *parsing, t_game *game)
{
	t_vector	*vec;
	size_t		index;
	t_property	*prop;

	index = 0;
	vec = parsing->entities_cache;
	while(index < vec->total)
	{
		prop = (t_property *)vec->get(vec, index);
		if (!prop)
			break;
		build_entity(prop, game);
		index++;
	}
	vector_free(parsing->entities_cache, true);
	parsing->entities_cache = NULL;
}

static inline const t_entity_mapping	*get_constructors(char *token);

static inline void	build_entity(t_property *prop, t_game *game)
{
	const t_entity_mapping		*data = get_constructors(prop->argv[0]);
	t_entity					*entity;
	t_vec3						pos;

	if (!data || !data->constructor)
		throw_error(game, ERROR_PROPERTY_ENTITY_UNKNOWN);
	pos = (t_vec3){ft_atof(prop->argv[1]),
		ft_atof(prop->argv[2]), ft_atof(prop->argv[3])};
	entity = data->constructor(pos, game);
	if (!entity)
		throw_error(game, ERROR_ENTITIES_ALLOC);
	if (entity->data_constructor && entity->data_constructor(entity,
			(t_property){prop->argv + 4, prop->argc - 4}, game) == false)
	{
		entity_free(entity);
		throw_error(game, data->error);
	}
	entity_add(entity, game);
}

/*Function to get constructors from token, 
for each entities token add an entry into the factory array*/

static inline const t_entity_mapping	*get_constructors(char *token)
{
	size_t							index;
	static const t_entity_mapping	factory[] = {
	{"NPC", entity_new_npc, ERROR_ENTITY_NPC},
	{NULL, NULL, 0}};

	index = 0;
	while (factory[index].constructor != NULL)
	{
		if (ft_strcmp(token, factory[index].token) == 0)
			return (&factory[index]);
		index++;
	}
	return (NULL);
}

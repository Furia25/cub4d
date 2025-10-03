/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   property_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 03:02:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 19:21:06 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

static inline void					build_entity(char *line, t_prop_input prop,
										t_game *game);

void	parse_property_entity(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	parsing->temp_prop = property_get_args(line, type, game);
	if (!parsing->temp_prop.argv)
		throw_error(ERROR_PARSING_ALLOC, game);
	if (parsing->temp_prop.argc < 4)
		throw_error_info(ERROR_PROPERTY_ENTITY, line, game);
	build_entity(line, parsing->temp_prop, game);
}

static inline void	build_entity(char *line, t_prop_input prop, t_game *game)
{
	t_entity_type	type = entity_get_from_token(prop.argv[0]);
	t_vec3			pos;

	if (type == ENTITY_UNKNOWN)
		throw_error_info(ERROR_PROPERTY_ENTITY_UNKNOWN, line, game);
	if (!ft_strcheck(prop.argv[1], is_fdigit)
		|| !ft_strcheck(prop.argv[2], is_fdigit)
		|| !ft_strcheck(prop.argv[3], is_fdigit))
		throw_error_info(ERROR_PROPERTY_ENTITY, line, game);
	pos = (t_vec3){ft_atof(prop.argv[1]),
		ft_atof(prop.argv[2]), ft_atof(prop.argv[3])};
	entity_instantiate(type, pos, &prop, game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:06:22 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/30 18:11:13 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline t_property_type	get_property_type(char *line);
static inline void				parse_property(char *line,
									t_property_type type,
									t_parsing *parsing,
									t_game *game);

void	interpret_map_from_file(t_parsing *parsing, t_game *game)
{
	char				*line;
	int					index;
	t_property_type		type;

	index = 0;
	while (index < parsing->file_length && parsing->file_content[index])
	{
		line = parsing->file_content[index];
		if (is_str_empty(line))
		{
			index++;
			continue ;
		}
		type = get_property_type(line);
		if (type == PROP_UNKNOWN)
			break ;
		parse_property(line, type, parsing, game);
		free_tab((void **)parsing->temp_prop.argv);
		parsing->temp_prop.argv = NULL;
		index++;
	}
	if (index >= parsing->file_length)
		throw_error(game, ERROR_PARSING_VALIDITY);
	try_parse_map(index, parsing, game);
}

static inline t_property_type	get_property_type(char *line)
{
	int			index;
	const char	*token;

	index = 0;
	while (index < PROP_UNKNOWN && g_property_token[index])
	{
		token = g_property_token[index];
		if (ft_strncmp(line, token, ft_strlen(token)) == 0)
			return ((t_property_type)index);
		index++;
	}
	return (PROP_UNKNOWN);
}

static inline void	parse_property(char *line, t_property_type type,
						t_parsing *parsing, t_game *game)
{
	if (type == PROP_NO || type == PROP_EA || type == PROP_SO
			|| type == PROP_WE)
		parse_property_wall(line, type, parsing, game);
	if (type == PROP_A || type == PROP_C || type == PROP_F)
	{
		if (type == PROP_C)
			parsing->has_ceil = true;
		else if (type == PROP_F)
			parsing->has_floor = true;
		parse_property_color(line, type, parsing, game);
	}
	if (type == PROP_ENTITY)
		parse_property_entity(line, type, parsing, game);
	if (type == PROP_HEIGHT)
		parse_property_height(line, type, parsing, game);
	if (type == PROP_BROADCAST)
		parse_property_broadcast(line, game);
}

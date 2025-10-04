/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:44:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/04 20:47:43 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"

size_t	arguments_length(t_argument *args)
{
	size_t	length;

	if (!args)
		return (0);
	length = 0;
	while (args[length].type != DT_NULL)
		length++;
	return (length);
}

void	property_check_inputs(t_prop_input *inputs,
			t_property *property, t_game *game)
{
	const size_t	length = arguments_length(property->args);

	if (inputs->argc < length)
		throw_error_property(property, ERROR_PROP_MISSING, game);
	if (property->variable && inputs->argc > length)
		throw_error_property(property, ERROR_PROP_TOOMANY, game);
}

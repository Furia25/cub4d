/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:44:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 02:05:46 by vdurand          ###   ########.fr       */
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

t_error	parse_arguments(int depth, void ***values,
			t_argument *args, char **tokens)
{
	const size_t		length = arguments_length(args);
	t_argument			*argument;
	size_t				index;
	t_error				error;

	index = 0;
	error = ERROR_NONE;
	while (index < length)
	{
		argument = &args[index];
		if (argument->array)
			error = handle_array(index, depth, argument, tokens[index]);
		else if (argument->type == DT_STRUCT)
			error = handle_struct(index, depth, argument, tokens[index]);
		else if (argument->type == DT_ENUM)
			error = handle_enum(index, argument, tokens[index]);
		else if (argument->type == DT_STRING)
			error = handle_string(index, argument, tokens[index]);
		else
			error = handle_scalar(index, argument, tokens[index]);
		index++;
	}
	return (error);
}

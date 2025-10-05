/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:44:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 05:05:34 by vdurand          ###   ########.fr       */
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

static inline t_error	parse_datatype(int depth, char *token,
							void **value, t_argument *argument)
{
	t_error	error;

	if (argument->type == DT_STRUCT)
		error = handle_struct(depth, token, value, argument);
	else if (argument->type == DT_ENUM)
		error = handle_enum(token, value, argument);
	else if (argument->type == DT_STRING)
		error = handle_string(token, value, argument);
	else if (argument->type == DT_FLOAT)
		error = handle_float(token, value, argument);
	else if (argument->type == DT_INT)
		error = handle_int(token, value, argument);
	return (error);
}

t_error	parse_arguments(int depth, void **values,
			t_argument *args, char **tokens)
{
	const size_t		length = arguments_length(args);
	t_argument			*arg;
	size_t				index;
	t_error				error;

	index = 0;
	error = ERROR_NONE;
	while (index < length)
	{
		arg = args + index;
		if (!arg->optional || tokens[index][0] == '\0')
		{
			if (arg->array && *values)
				error = handle_array(depth, tokens[index], values + index, arg);
			else
				error = parse_datatype(depth, tokens[index], values + index, arg);
		}
		if (error == ERROR_BASIC || error == ERROR_PARSING_ALLOC)
			return (error);
		else if (error != ERROR_NONE)
			print_error_argument(depth, error, tokens[index], arg);
		index++;
	}
	return (error);
}

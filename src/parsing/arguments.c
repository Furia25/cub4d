/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:44:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 03:26:32 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"

size_t	arguments_length(const t_argument *args)
{
	size_t	length;

	if (!args)
		return (0);
	length = 0;
	while (args[length].type != DT_NULL && args[length].name)
		length++;
	return (length);
}

size_t	arguments_count_required(const t_argument *args)
{
	size_t	index;
	size_t	length;

	if (!args)
		return (0);
	index = 0;
	length = 0;
	while (args[index].type != DT_NULL && args[index].name)
	{
		if (args[index].optional == false)
			length++;
		index++;
	}
	return (length);
}

t_error	parse_datatype(int depth, char *token,
			void **value, t_argument *argument)
{
	t_error	error;

	error = ERROR_NONE;
	if (!token || !token[0] || !value || !argument)
		return (ERROR_ARG_INCOMPLETE);
	if (argument->type == DT_NULL)
		return (ERROR_NONE);
	else if (argument->array > 0)
		error = handle_array(depth, token, value, argument);
	else if (argument->type == DT_STRUCT)
		error = handle_struct(depth, token, value, argument);
	else if (argument->type == DT_ENUM)
		error = handle_enum(token, value, argument);
	else if (argument->type == DT_STRING)
		error = handle_string(token, value, argument);
	else if (argument->type == DT_FLOAT)
		error = handle_float(token, value, argument);
	else if (argument->type == DT_INT)
		error = handle_int(token, value, argument);
	else if (argument->type == DT_UINT)
		error = handle_uint(token, value, argument);
	return (error);
}

t_error	parse_arguments(int depth, void **values,
			const t_argument *args, char **tokens)
{
	const size_t		length = arguments_length(args);
	t_argument			*arg;
	size_t				index;
	t_error				exit_error;
	t_error				error;

	index = 0;
	exit_error = ERROR_NONE;
	while (index < length)
	{
		arg = (t_argument *)args + index;
		if (!arg->optional || (tokens[index] && tokens[index][0] == '\0'))
		{
			error = parse_datatype(depth, tokens[index], values + index, arg);
			if (error == ERROR_PARSING_ALLOC)
				return (ERROR_PARSING_ALLOC);
			else if (error != ERROR_NONE)
			{
				if (!argument_error_register(depth, error, tokens[index], arg))
					return (ERROR_PARSING_ALLOC);
				exit_error = ERROR_ARG_INVALID;
			}
		}
		index++;
	}
	return (exit_error);
}

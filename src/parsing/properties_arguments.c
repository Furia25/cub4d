/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:44:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 20:05:35 by vdurand          ###   ########.fr       */
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
	if (!token || !value || !argument)
		return (ERROR_ARG_INCOMPLETE);
	if (argument->type == DT_NULL)
		return (ERROR_NONE);
	else if (argument->array)
		handle_array(depth, token, value, argument);
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

int	parse_arguments(int depth, void **values,
			const t_argument *args, char **tokens)
{
	const size_t		length = arguments_length(args);
	t_argument			*arg;
	size_t				index;
	int					exit_code;
	t_error				error;

	index = 0;
	exit_code = 0;
	while (index < length)
	{
		arg = (t_argument *)args + index;
		if (arg->optional && (!tokens[index] || tokens[index][0] == '\0'))
		{
			values[index] = NULL;
			index++;
			continue ;
		}
		error = parse_datatype(depth, tokens[index], values + index, arg);
		if (error == ERROR_BASIC || error == ERROR_PARSING_ALLOC)
			return (2);
		else if (error != ERROR_NONE)
		{
			print_error_argument(depth, error, tokens[index], arg);
			exit_code = 1;
		}
		index++;
	}
	return (exit_code);
}

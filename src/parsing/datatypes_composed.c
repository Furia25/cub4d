/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes_composed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:01:35 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 03:25:28 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parsing.h"

t_error	handle_struct(int depth, char *pretoken, void **value, t_argument *arg)
{
	const t_data_subtype_info	*subtype = &g_data_subtype_info[arg->subtype];
	char						**tokens;
	size_t						arg_needed;
	size_t						length;
	t_error						error;

	if (!pretoken || !dt_check_prefix(pretoken, arg))
		return (ERROR_ARG_MALFORMED_STRUCT);
	arg_needed = arguments_length(subtype->fields);
	*value = ft_calloc(arg_needed + 1, sizeof(void *));
	if (!(*value))
		return (ERROR_PARSING_ALLOC);
	tokens = tokenize(pretoken, TOKEN_DELIMITER, TOKEN_ENCLOSERS, &length);
	if (!tokens)
		return (ERROR_PARSING_ALLOC);
	if (arg_needed != length)
	{
		free_tab((void **)tokens);
		return (ERROR_ARG_INCOMPLETE);
	}
	error = parse_arguments(depth, *value,
		subtype->fields, tokens);
	free_tab((void **)tokens);
	return (error);
}

# define ARRAY_CONTENT_STR	"element  "

static inline bool	array_init_template(t_dt_array *array, t_argument *argument)
{
	size_t	temp_length;
	size_t	name_length;

	name_length = ft_strlen(ARRAY_CONTENT_STR);
	temp_length = array->length;
	while (temp_length != 0)
	{
		temp_length /= 10;
		name_length++;
	}
	array->template = *argument;
	array->base_arg = argument;
	array->template.array = array->template.array - 1;
	array->template.optional = false;
	array->template.name = ft_calloc(name_length, sizeof(char));
	if (!array->template.name)
		return (false);
	ft_strcpy(array->template.name, ARRAY_CONTENT_STR);
	return (true);
}

static inline t_error	parse_array(int depth, char **tokens,
							t_dt_array *array, t_argument *arg)
{
	t_error		temp_error;
	size_t		index;
	t_error		error;

	index = 0;
	error = ERROR_NONE;
	if (!array_init_template(array, arg))
		return (ERROR_PARSING_ALLOC);
	while (index < array->length)
	{
		ft_itoab(index, array->template.name, ft_strlen(ARRAY_CONTENT_STR) - 1);
		temp_error = parse_datatype(depth + 1, tokens[index],
			array->values + index, &array->template);
		if (temp_error == ERROR_PARSING_ALLOC || temp_error == ERROR_BASIC)
			return (ERROR_PARSING_ALLOC);
		else if (temp_error != ERROR_NONE)
		{
			if (!argument_error_register(depth, temp_error,
				tokens[index], &array->template))
				return (ERROR_PARSING_ALLOC);
			error = ERROR_ARG_ARRAY_CONTENT;
		}
		index++;
	}
	return (error);
}

t_error	handle_array(int depth, char *pretoken, void **value, t_argument *arg)
{
	char		**tokens;
	size_t		length;
	t_error		error;

	if (!pretoken || !dt_check_prefix(pretoken, arg))
		return (ERROR_ARG_MALFORMED_ARRAY);
	tokens = tokenize(pretoken, TOKEN_DELIMITER, TOKEN_ENCLOSERS, &length);
	if (!tokens)
		return (ERROR_PARSING_ALLOC);
	if (arg->array_size != 0 && length != arg->array_size)
	{
		free_tab((void **)tokens);
		return (ERROR_ARG_ARRAY_SIZE);
	}
	*value = ft_calloc(1, sizeof(t_dt_array) + ((length + 1) * sizeof(void *)));
	if (!(*value))
	{
		free_tab((void **)tokens);
		return (ERROR_PARSING_ALLOC);
	}
	((t_dt_array *)*value)->length = length;
	error = parse_array(depth + 1, tokens, *value, arg);
	free_tab((void **)tokens);
	return (error);
}

t_error	handle_enum(char *token, void **value, t_argument *arg)
{
	const t_data_subtype_info	*subtype = &g_data_subtype_info[arg->subtype];
	size_t						index;

	if (!subtype->enum_values)
		return (ERROR_ARG_INVALID);
	index = 0;
	while (index < subtype->count)
	{
		if (ft_strcmp(subtype->enum_values[index], token) == 0)
		{
			*value = ft_calloc(1, sizeof(size_t));
			if (!(*value))
				return (ERROR_PARSING_ALLOC);
			*((size_t *)(*value)) = index;
			return (ERROR_NONE);
		}
		index++;
	}
	return (ERROR_ARG_INVALID);
}

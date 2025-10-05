/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes_composed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:01:35 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 18:32:37 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parsing.h"

t_error	handle_struct(int depth, char *pretoken, void **value, t_argument *arg)
{
	const t_data_subtype_info	*subtype = &g_data_subtype_info[arg->subtype];
	char						**tokens;
	size_t						arg_length;
	size_t						tokens_length;
	t_error						error;

	if (!pretoken || !dt_check_prefix(pretoken, arg))
		return (ERROR_ARG_MALFORMED_STRUCT);
	arg_length = arguments_length(subtype->fields);
	*value = ft_calloc(arg_length + 1, sizeof(void *));
	if (!(*value))
		return (ERROR_PARSING_ALLOC);
	tokens = tokenize(pretoken, TOKEN_DELIMITER,
		TOKEN_ENCLOSERS, &tokens_length);
	if (!tokens)
		return (ERROR_PARSING_ALLOC);
	if (arg_length != tokens_length)
	{
		free_tab((void **)tokens);
		return (ERROR_ARG_INCOMPLETE);
	}
	error = parse_arguments(depth + 1, *value,
		subtype->fields, tokens);
	free_tab((void **)tokens);
	return (error);
}

static inline t_error	parse_array(int depth, char **tokens,
							void **values, t_argument *arg)
{
	t_argument	template;
	t_error		error;
	size_t		length;
	size_t		index;

	length = tab_length((void **)tokens);
	template = *arg;
	template.array = false;
	template.optional = false;
	index = 0;
	error = ERROR_NONE;
	while (index < length)
	{
		error = parse_datatype(depth + 1, tokens[index],
			values + index, &template);
		if (error == ERROR_PARSING_ALLOC || error == ERROR_BASIC)
			break ;
		else if (error != ERROR_NONE)
			print_error_argument(depth, error, tokens[index], &template);
		index++;
	}
	return (error);
}

t_error	handle_array(int depth, char *pretoken, void **value, t_argument *arg)
{
	char	**tokens;
	size_t	length;
	t_error	error;

	if (!pretoken || !dt_check_prefix(pretoken, arg))
		return (ERROR_ARG_MALFORMED_STRUCT);
	tokens = tokenize(pretoken, TOKEN_DELIMITER, TOKEN_ENCLOSERS, &length);
	if (!tokens)
		return (ERROR_PARSING_ALLOC);
	if (arg->array_size != 0 && length != arg->array_size)
	{
		free_tab((void **)tokens);
		return (ERROR_ARG_ARRAY_SIZE);
	}
	*value = ft_calloc(length + 1, sizeof(void *));
	if (!(*value))
	{
		free_tab((void **)tokens);
		return (ERROR_PARSING_ALLOC);
	}
	error = parse_array(depth + 1, tokens, (void **)*value, arg);
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
